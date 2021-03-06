# WarGame

## 初级软件设计实作：兵棋进攻游戏

使用Qt 6.1开发。

功能需求：

1. 软件启动时，显示一个游戏运行区，游戏区是以n*m个方格组成的矩形区域(n、m≥10)
2. 在游戏区中，用户的k个棋子(k≥3)放在最右边（在最右边的具体位置随机），每个棋子占据一个格子，每个棋子有生命值（随机）。“进攻目标区”（一个格子）在游戏区的最左边（在最左边的具体位置随机）。
3. 在游戏区中，软件随机生成5个以上的“障碍”（棋子不可跨越这些障碍，必须绕行）和4个以上的防守点，它们的位置均随机。防守点的射程由程序代码设定。
4. 当游戏开始启动后，在每一轮中，用户用鼠标或键盘控制其所有棋子移动，每个棋子每轮最多只能走一步（只能上下或左右走，不能斜走）。当用户完成所有棋子移动后，完成本轮用户操作。
5. 在用户完成操作后，防守点会向进入其射程的所有棋子进行射击（每次射击导致棋子生命值的下降值，由程序设定）。如果棋子的生命值耗尽，则该棋子消失。
6. 不断重复第4、5步，直到有棋子到达进攻目标区（获胜），或者所有棋子消失（失败）

相关技术：

1. 图像展现
2. 随机数使用
3. 鼠标、键盘消息处理

## Author

5t4r1i9ht admin@5t4r1i9ht.com

## 截图

![截图](./截图.png)

## License

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
