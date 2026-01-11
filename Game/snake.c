// 引入标准输入输出库（用于 printf, scanf 等）
#include <stdio.h>

// 引入标准库（用于 system, rand, srand 等）
#include <stdlib.h>

// 引入控制台输入库（用于 _kbhit, _getch，仅 Windows 支持）
#include <conio.h>

// 引入 Windows API 库（用于 Sleep 函数）
#include <windows.h>

// 引入时间库（用于 time 函数，初始化随机种子）
#include <time.h>

// 定义游戏区域宽度为 30 个字符
#define WIDTH 30

// 定义游戏区域高度为 20 行
#define HEIGHT 20

// 定义蛇的最大长度：不能超过整个地图的格子数（防止数组越界）
#define MAX_SNAKE (WIDTH * HEIGHT)

// 定义方向枚举类型：STOP=未开始，UP=上，DOWN=下，LEFT=左，RIGHT=右
enum Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };

// 全局数组：存储蛇每一节的 X 坐标（最多 MAX_SNAKE 节）
int snakeX[MAX_SNAKE];

// 全局数组：存储蛇每一节的 Y 坐标
int snakeY[MAX_SNAKE];

// 全局变量：当前蛇的实际长度（初始为 3）
int snakeLen;

// 全局变量：当前蛇的移动方向（初始为 STOP）
enum Direction dir;

// 全局变量：食物的 X 坐标
int foodX;

// 全局变量：食物的 Y 坐标
int foodY;

// 全局变量：玩家得分
int score;

// 全局变量：游戏是否结束（0=进行中，1=已结束）
int gameOver;

// 函数声明：初始化游戏状态
void setup();

// 函数声明：绘制游戏画面
void draw();

// 函数声明：处理键盘输入
void input();

// 函数声明：更新游戏逻辑（移动、碰撞、吃食物等）
void logic();

// 函数声明：在地图上生成新食物
void generateFood();

// 主函数：程序入口
int main() {
    // 调用 setup 初始化游戏（蛇位置、食物、分数等）
    setup();

    // 游戏主循环：只要游戏未结束，就不断循环
    while (!gameOver) {
        draw();   // 绘制当前帧画面
        input();  // 检查并处理用户按键
        logic();  // 更新蛇的位置、检测碰撞、处理食物等
        Sleep(120); // 暂停 120 毫秒，控制游戏速度（值越小越快）
    }

    // 游戏结束后清屏
    system("cls");

    // 打印 Game Over 标题
    printf("\n\n");
    printf("\t\t####################\n");
    printf("\t\t#    Game Over!    #\n");
    printf("\t\t####################\n");

    // 显示最终得分
    printf("\t\t    Your Score: %d\n", score);

    // 提示用户按任意键退出
    printf("\n\tPress any key to exit...\n");

    // 等待用户按键，防止窗口立即关闭（避免“闪退”）
    _getch();

    // 程序正常退出
    return 0;
}

// 初始化游戏状态
void setup() {
    // 使用当前时间作为随机种子，确保每次运行食物位置不同
    srand((unsigned int)time(NULL));

    // 重置游戏结束标志
    gameOver = 0;

    // 初始方向设为 STOP（等待玩家按键才开始移动）
    dir = STOP;

    // 分数归零
    score = 0;

    // 初始蛇长度为 3 节
    snakeLen = 3;

    // 计算地图中心点坐标
    int cx = WIDTH / 2;  // 中心 X（列）
    int cy = HEIGHT / 2; // 中心 Y（行）

    // 设置蛇头在中心
    snakeX[0] = cx;
    snakeY[0] = cy;

    // 第二节在蛇头左边
    snakeX[1] = cx - 1;
    snakeY[1] = cy;

    // 第三节在第二节左边（蛇向左延伸）
    snakeX[2] = cx - 2;
    snakeY[2] = cy;

    // 在地图上生成第一个食物
    generateFood();
}

// 绘制游戏画面
void draw() {
    // 清除控制台屏幕（简单但有效，会有轻微闪烁）
    system("cls");

    // 绘制上边框：打印 WIDTH+2 个 '#'（左右各多一个墙）
    for (int i = 0; i < WIDTH + 2; i++) 
        printf("#");
    printf("\n"); // 换行

    // 逐行绘制游戏区域（共 HEIGHT 行）
    for (int y = 0; y < HEIGHT; y++) {
        printf("#"); // 每行开头打印左墙

        // 逐列绘制该行内容（共 WIDTH 列）
        for (int x = 0; x < WIDTH; x++) {
            // 如果当前位置是食物，打印 '@'
            if (x == foodX && y == foodY) {
                printf("@");
            } else {
                // 否则检查是否是蛇的身体
                int isSnake = 0; // 标记是否为蛇

                // 遍历蛇的所有节
                for (int i = 0; i < snakeLen; i++) {
                    // 如果某节蛇的位置等于当前 (x,y)
                    if (snakeX[i] == x && snakeY[i] == y) {
                        printf("O"); // 打印蛇身
                        isSnake = 1; // 标记已找到
                        break;       // 跳出内层循环
                    }
                }

                // 如果不是蛇也不是食物，打印空格
                if (!isSnake) 
                    printf(" ");
            }
        }

        // 每行末尾打印右墙并换行
        printf("#\n");
    }

    // 绘制下边框
    for (int i = 0; i < WIDTH + 2; i++) 
        printf("#");
    printf("\n");

    // 显示当前得分
    printf("\tScore: %d\n", score);

    // 如果游戏尚未开始（方向仍为 STOP），提示玩家操作
    if (dir == STOP) {
        printf("\t>>> Use arrow keys to start! <<<\n");
    }

    // 显示退出提示
    printf("\tPress 'X' to quit.\n");
}

// 处理键盘输入
void input() {
    // 检查是否有按键被按下（_kbhit 返回非 0 表示有）
    if (_kbhit()) {
        // 读取一个字符（不回显）
        char ch = _getch();

        // 如果是特殊键（如方向键），会先返回 0 或 224
        if (ch == 0 || ch == 224) {
            ch = _getch(); // 再读一次，获取实际的方向码
        }

        // 根据按键设置方向（禁止 180° 急转弯）
        switch (ch) {
            case 72: // 上箭头（ASCII 扩展码）
                if (dir != DOWN) dir = UP;    // 不能从下直接变上
                break;
            case 80: // 下箭头
                if (dir != UP)   dir = DOWN;  // 不能从上直接变下
                break;
            case 75: // 左箭头
                if (dir != RIGHT)dir = LEFT;  // 不能从右直接变左
                break;
            case 77: // 右箭头
                if (dir != LEFT) dir = RIGHT; // 不能从左直接变右
                break;
            case 'x': // 小写 x
            case 'X': // 大写 X
                gameOver = 1; // 设置游戏结束标志
                break;
        }
    }
}

// 更新游戏逻辑
void logic() {
    // 如果方向仍是 STOP（玩家未按方向键），不做任何操作
    if (dir == STOP) {
        return;
    }

    // 获取当前蛇头的位置（第 0 节）
    int headX = snakeX[0];
    int headY = snakeY[0];

    // 根据当前方向计算新蛇头位置
    switch (dir) {
        case UP:    headY--; break;    // 向上：Y 减 1
        case DOWN:  headY++; break;    // 向下：Y 加 1
        case LEFT:  headX--; break;    // 向左：X 减 1
        case RIGHT: headX++; break;    // 向右：X 加 1
    }

    // 撞墙检测：如果新蛇头超出地图边界
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
        gameOver = 1; // 游戏结束
        return;       // 提前退出函数
    }

    // 撞自己检测：从第 1 节身体开始比较（跳过蛇头自身）
    for (int i = 1; i < snakeLen; i++) {
        if (snakeX[i] == headX && snakeY[i] == headY) {
            gameOver = 1; // 蛇头撞到身体
            return;
        }
    }

    // 检查是否吃到食物
    if (headX == foodX && headY == foodY) {
        // 防止蛇长超过数组上限
        if (snakeLen < MAX_SNAKE - 1) {
            snakeLen++;      // 蛇变长一节
            score += 10;     // 得 10 分
            generateFood();  // 生成新食物
        } else {
            // 地图已满，胜利或结束
            gameOver = 1;
        }
    } else {
        // 没吃到食物：需要移动身体（从尾部向前覆盖）
        for (int i = snakeLen - 1; i > 0; i--) {
            snakeX[i] = snakeX[i - 1]; // 前一节的位置赋给当前节
            snakeY[i] = snakeY[i - 1];
        }
    }

    // 更新蛇头位置为新计算的位置
    snakeX[0] = headX;
    snakeY[0] = headY;
}

// 在地图上生成新食物（确保不在蛇身上）
void generateFood() {
    int valid; // 标记食物位置是否有效

    do {
        valid = 1; // 假设位置有效

        // 随机生成食物坐标（X 在 [0, WIDTH-1]，Y 在 [0, HEIGHT-1]）
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;

        // 检查食物是否与蛇体重叠
        for (int i = 0; i < snakeLen; i++) {
            if (snakeX[i] == foodX && snakeY[i] == foodY) {
                valid = 0; // 无效，需重新生成
                break;
            }
        }
    } while (!valid); // 只要无效，就循环重试
}