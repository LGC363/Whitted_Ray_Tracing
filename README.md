1.项目概述：一个简易的光线追踪器，参考了RayTracingInOneWeekend和RayTracingTheNextWeek

--该光线追踪器实现了世界场景类（包含所有HittableObject）:

world一开始定义为hittbale_list，其中的数组包含所有的物体，当物体都被添加到数组之后，使用
world = hittable_list(make_shared<bvh_node>(world));
调用了bvh_node类的构造函数，bvh_node和hittable_list是同一级的类，都继承hittable。
world还是hittable_list，它的数组只包含一个基于它自己的bvh_node。
bvh_node没有数组，有right和left节点，在构造函数中，left指向bvh_node，包含原来物体的前一半，right同理，这是递归进行的。
也就是说，原先的物体数组看作一行叶子节点，使用bvh_node的left和right，每个bvh_node连接两个相邻物体，并扩充包围范围，直到囊括所有物体，拿到最终根节点，也就是world的原来的数组中仅剩的一个bvh_node。
bvh树状结构，叶子节点为obj，其余为bvh_node，其中bvh_node有包围范围，有left和right，可以进入查看它们的包围范围，一直查找递归到叶子，才会调用sphere的hit函数判断相交。

--相机类（具有render方法（递归），使用单像素多光线求平均抗锯齿，以世界场景为参数）:

render方法有三层循环，前两层为图像像素的遍历，最后一层为多条光线抗锯齿，然后进入ray_color递归，第一层ray_color是从相机出发的光线，后续的ray_color是通过材质得到的反射光线

--实现了材质基类（在此基础可自定义材质子类）和部分材料类（电介质材质，漫反射材质，金属材质）:

主要是材质的scatter函数，类似于brdf函数，传入光线和hit_record（相交点位置和向量），传出attenuation（就是材质的颜色）和反射光线


--实现了运动模糊:

给光线加上时间，原本一个像素发出多条光线抗锯齿，现在这些光线具有不同的时间，在判断与运动物体相交时加上时间因素，这样每条光线带回的信息就是不同帧的运动物体的信息，然后通过这些光线的加权平均，间接实现了运动物体不同帧的平均，从而实现运动模糊

--光线，颜色，向量运算等类

