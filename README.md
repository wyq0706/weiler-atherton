# weiler-atherton多边形裁剪
多边形裁剪采用Weiler-Atherton算法。被裁减多边形可以是任意多边形：凸、凹、带内环等。约定顶点序列方向：外环（逆时针）；内环（顺时针）。

流程如下：

1. 建主多边形和裁剪多边形的顶点表；

2. 求交点、归类，并按顺序插入到顶点表中，
   在两个表的相应顶点间建双向指针；

3. 裁剪：

   3.1. 如果还有未跟踪过的交点，则任取一个作为起点，建空的裁剪结果多边形顶点表，把该交点入结果顶点表。否则算法结束；
   3.2。 如果该交点为入点，在主多边形顶点表内跟踪，否则在裁剪多边形顶点表内跟踪；
   3.3。 如果跟踪到的是多边形顶点，将其加入结果顶点表，继续跟踪，直到遇到新的交点，重复3.2~3.3，直到回到起点。
   
### 交互方式

1. 在画布上左键单击，**逆时针**选点画外环。

2. 点击"闭合多边形"按钮，闭合外环。

3. 继续在画布上左键单击，**顺时针**选点画内环。

4. 点击"闭合多边形"按钮，闭合内环，转3，可画多个内环。

5. 点击"完成当前多边形绘画"按钮结束绘制当前多边形。默认第一个多边形为主多边形。

6. 重复1-5绘制第二个多边形，默认为裁剪多边形。

7. 点击“裁剪”，即可得到裁剪结果。

![image](https://github.com/wyq0706/weiler-atherton/blob/main/images/735bc19ff3a5fffbc5caf70a5946526.png)
![image](https://github.com/wyq0706/weiler-atherton/blob/main/images/28d7fed25ec8034c60ba492db239a2b.png)
