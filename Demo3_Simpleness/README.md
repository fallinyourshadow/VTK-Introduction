# 使用Qt编写简单的接口，实现模型属性的更变和部分数据格式文件的导入导出。
## GeometryItem类
 - 继承于QStandardItem类
 - 用于记录模型的绝对坐标，颜色，角度， vtkactor，vtkmapper
## PrismItem类 棱柱
 - 继承于GeometryItem类
 - 记录了棱柱的高，半径，棱数，vtksource
## PyramidItem类 棱锥
 - 继承于GeometryItem类
 - 记录了棱锥的高，半径，棱数，vtksource
## SphereItem类 球体
 - 继承于GeometryItem类
 - 记录了球体的θ分辨率和Φ分辨率，vtksource
## PropertiesWidget 包含所有属性的用户接口控件，选择不同的对象后会显示对应的相关属性
## ListView 记录和显示当前渲染窗口中的所有图形Item
