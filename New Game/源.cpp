#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<graphics.h>
#include<math.h>
#pragma comment( lib, "MSIMG32.LIB")

//窗口大小
#define WIDTH 1280
#define HEIGHT 720

//开始菜单图片
IMAGE StartMenuImg[4];

//第一关背景图片
IMAGE FirstStageBackgroundImg[2];

//第二关背景图片
IMAGE SecondStageBackGroundImg[5];

//第一关第一个过场动画图片
IMAGE PterosureImg[5];

//掉落物食品图片
IMAGE FoodImg[5];


//汉娜头像
IMAGE HannahAvatarImg;

//汉娜防御图片
IMAGE HannahDefensiveImgLeft;
IMAGE HannahDefensiveImgRight;

//汉娜踢腿图片
IMAGE HannahKickImg[12];

//汉娜静止撩头发图片
IMAGE HannahStillImgLeft[4];
IMAGE HannahStillImgRight[4];

//汉娜走路图片
IMAGE HannahWalkImgLeft[12];
IMAGE HannahWalkImgRight[12];

//汉娜跑步图片
IMAGE HannahRunImgLeft[9];
IMAGE HannahRunImgRight[9];

//汉娜攻击图片
IMAGE HannahAttackImgLeft[8];
IMAGE HannahAttackImgRight[8];

//汉娜被击倒图片
IMAGE HannahWasKnockedDownImgLeft[6];
IMAGE HannahWasKnockedDownImgRight[6];

//汉娜胜利图片
IMAGE HannahVictoryImgLeft[5];
IMAGE HannahVictoryImgRight[5];

//小怪A头像
IMAGE EnemyAAvatarImg;

//小怪A防御图片
IMAGE EnemyADefensiveImgLeft;
IMAGE EnemyADefensiveImgRight;

//小怪A被击倒图片
IMAGE EnemyAWasKnockedDownImgLeft[5];
IMAGE EnemyAWasKnockedDownImgRight[5];

//小怪A走路图片
IMAGE EnemyAWalkImgLeft[7];
IMAGE EnemyAWalkImgRight[7];

//小怪A攻击图片
IMAGE EnemyAAttackImgLeft[9];
IMAGE EnemyAAttackImgRight[9];

//小怪A静止图片
IMAGE EnemyAStillImgLeft[3];
IMAGE EnemyAStillImgRight[3];

//小怪A特殊姿势图片
IMAGE EnemyASpecialImg[3];

//小怪B头像
IMAGE EnemyBAvatarImg;

//小怪B防御图片
IMAGE EnemyBDefensiveImgLeft;
IMAGE EnemyBDefensiveImgRight;	

//小怪B被击倒图片
IMAGE EnemyBWasKnockedDownImgLeft[5];
IMAGE EnemyBWasKnockedDownImgRight[5];

//小怪B走路图片
IMAGE EnemyBWalkImgLeft[7];
IMAGE EnemyBWalkImgRight[7];

//小怪B攻击图片
IMAGE EnemyBAttackImgLeft[9];
IMAGE EnemyBAttackImgRight[9];

//小怪B静止图片
IMAGE EnemyBStillImgLeft[3];
IMAGE EnemyBStillImgRight[3];

//小怪C头像
IMAGE EnemyCAvatarImg;

//小怪C防御图片
IMAGE EnemyCDefensiveImgLeft;
IMAGE EnemyCDefensiveImgRight;

//小怪C冲撞图片
IMAGE EnemyCCollideImgLeft[6];
IMAGE EnemyCCollideImgRight[6];

//小怪C被击倒图片
IMAGE EnemyCWasKnockedDownImgLeft[5];
IMAGE EnemyCWasKnockedDownImgRight[5];

//小怪C走路图片
IMAGE EnemyCWalkImgLeft[5];
IMAGE EnemyCWalkImgRight[5];

//小怪C静止图片
IMAGE EnemyCStillImgLeft[9];
IMAGE EnemyCStillImgRight[9];

enum
{
	StartMenu,

	FirstStageFirstCutscene,
	FirstStageSecondCutscene,
	FirstStageThirdCutscene,
	FirstStageFourthCutscene,
	FirstStageEnd,
	FirstStage,

	SecondStageFirstCutscene,
	SecondStageSecondCutscene,
	SecondStage,

	ThirdStage,

	DefensivePosture,
	StillPosture,
	WalkPosture,
	RunPosture,
	AttackPosture,
	WasKonckedDown,
	RandWalk,
	TrackPosture,
	DeathPosture,
	CollidePosture,

	VictoryPosture,

	none,up,down,left,right,



};
int GameStatus = StartMenu;

struct cutscene
{
	double px;
	double py;
	double vx;
	double distance;
	DWORD BeginTime;
	DWORD ElapsedTime;
};
struct cutscene FirstStageFirst;
struct cutscene FirstStageSecond;
struct cutscene FirstStageThird;
struct cutscene SecondStageFirst;

struct character
{
	double px;
	double py;
	double vx;
	double vy;
	int status;
	int HorizontalDirection;
	int VerticalDirection;
	int WasAttackCnt;
	bool IsDead;
	double life;
	bool IsShouldRest;
	bool IsSpecialPosture;
	int flag;
	DWORD BeginTime;
	DWORD ElapsedTime;
	int WasAttackDirection;
	double distance;
};
struct character Hannah;
struct character EnemyA;
struct character EnemyB;
struct character EnemyC;

struct Dinosaur
{
	double px;
	double py;
	double vx;
	double vy;
	DWORD BeginTime;
	DWORD ElapsedTime;
};
struct Dinosaur Pterosaur[2];

struct icon
{
	double px;
	double py;
	double vx;
};
struct icon HannahAvatar;
struct icon EnemyAAvatar;
struct icon EnemyBAvatar;
struct icon EnemyCAvatar;

struct drop
{
	double px;
	double py;
	int status;
};
struct drop Food;

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void StartUp()
{
	//绘制窗口
	initgraph(WIDTH, HEIGHT);

	//加载开始菜单图片
	loadimage(&StartMenuImg[0], "./img/Menu/0.png");
	loadimage(&StartMenuImg[1], "./img/Menu/1.png");
	loadimage(&StartMenuImg[2], "./img/Menu/2.png");
	loadimage(&StartMenuImg[3], "./img/Menu/3.png");


	//加载第一关卡背景图像
	loadimage(&FirstStageBackgroundImg[0], "./img/Background/FirstStage/0.png");
	loadimage(&FirstStageBackgroundImg[1], "./img/Background/FirstStage/1.png");

	FirstStageFirst.px = 0;
	FirstStageFirst.py = 0;
	FirstStageFirst.vx = 1;
	FirstStageFirst.distance = 0;

	FirstStageThird.px = 1250;
	FirstStageThird.py = 0;
	FirstStageThird.vx = 1;
	FirstStageThird.distance = 0;

	//加载第二关卡背景图像
	loadimage(&SecondStageBackGroundImg[0], "./img/BackGround/SecondStage/0.png");
	loadimage(&SecondStageBackGroundImg[1], "./img/BackGround/SecondStage/1.png");
	loadimage(&SecondStageBackGroundImg[2], "./img/BackGround/SecondStage/2.png");
	loadimage(&SecondStageBackGroundImg[3], "./img/BackGround/SecondStage/3.png");
	loadimage(&SecondStageBackGroundImg[4], "./img/BackGround/SecondStage/4.png");

	SecondStageFirst.px = 0;
	SecondStageFirst.py = 0;
	SecondStageFirst.vx = 1;
	SecondStageFirst.distance = 0;
	SecondStageFirst.BeginTime = 0;
	SecondStageFirst.ElapsedTime = 250;


	//加载翼龙过场动画飞行图像
	loadimage(&PterosureImg[0], "./img/Pterosaur/0.png");
	loadimage(&PterosureImg[1], "./img/Pterosaur/1.png");
	loadimage(&PterosureImg[2], "./img/Pterosaur/2.png");
	loadimage(&PterosureImg[3], "./img/Pterosaur/3.png");
	loadimage(&PterosureImg[4], "./img/Pterosaur/4.png");

	Pterosaur[0].px = -200;
	Pterosaur[0].py = 300;
	Pterosaur[0].vx = 1.2;
	Pterosaur[0].vy = 0.5;
	Pterosaur[0].BeginTime = 0;
	Pterosaur[0].ElapsedTime = 100;

	Pterosaur[1].px = -100;
	Pterosaur[1].py = 500;
	Pterosaur[1].vx = 0.8;
	Pterosaur[1].vy = 0.6;
	Pterosaur[1].BeginTime = 0;
	Pterosaur[1].ElapsedTime = 100;

	//加载小怪A和B的过场动画
	FirstStageSecond.px = 1650;
	FirstStageSecond.py = 320;
	FirstStageSecond.BeginTime = 0;
	FirstStageSecond.ElapsedTime = 60;

	//加载掉落物食物图片
	loadimage(&FoodImg[0], "./img/Drop/Food/0.png");
	loadimage(&FoodImg[1], "./img/Drop/Food/1.png");
	loadimage(&FoodImg[2], "./img/Drop/Food/2.png");
	loadimage(&FoodImg[3], "./img/Drop/Food/3.png");
	loadimage(&FoodImg[4], "./img/Drop/Food/4.png");

	Food.px = -2000;
	Food.py = -2000;
	Food.status = 0;



	//加载汉娜头像
	loadimage(&HannahAvatarImg, "./img/Hannah/Avatar/0.png");

	HannahAvatar.px = 1800;
	HannahAvatar.py = 10;
	HannahAvatar.vx = 1.43;
	
	//加载小怪A头像
	loadimage(&EnemyAAvatarImg,"./img/SmallEnemyA/Avatar/0.png");

	EnemyAAvatar.px = 1800;
	EnemyAAvatar.py = 120;
	EnemyAAvatar.vx = 1.43;

	//加载小怪B头像
	loadimage(&EnemyBAvatarImg, "./img/SmallEnemyB/Avatar/0.png");

	EnemyBAvatar.px = 1800;
	EnemyBAvatar.py = 170;
	EnemyBAvatar.vx = 1.43;

	//加载小怪C头像
	loadimage(&EnemyCAvatarImg, "./img/SmallEnemyC/Avatar/0.png");
	EnemyCAvatar.px = 1670;
	EnemyCAvatar.py = 120;
	EnemyCAvatar.vx = 1.43;




	//加载防御姿态的汉娜图像-方向向左
	loadimage(&HannahDefensiveImgLeft, "./img/Hannah/DefensivePostureLeft/0.png");
	//加载防御姿态的汉娜图像-方向向右
	loadimage(&HannahDefensiveImgRight, "./img/Hannah/DefensivePostureRight/0.png");

	//加载汉娜踢腿图像
	loadimage(&HannahKickImg[0], "./img/Hannah/Kick/0.png");
	loadimage(&HannahKickImg[1], "./img/Hannah/Kick/1.png");
	loadimage(&HannahKickImg[2], "./img/Hannah/Kick/2.png");
	loadimage(&HannahKickImg[3], "./img/Hannah/Kick/3.png");
	loadimage(&HannahKickImg[4], "./img/Hannah/Kick/4.png");
	loadimage(&HannahKickImg[5], "./img/Hannah/Kick/5.png");
	loadimage(&HannahKickImg[6], "./img/Hannah/Kick/6.png");
	loadimage(&HannahKickImg[7], "./img/Hannah/Kick/7.png");
	loadimage(&HannahKickImg[8], "./img/Hannah/Kick/8.png");
	loadimage(&HannahKickImg[9], "./img/Hannah/Kick/9.png");
	loadimage(&HannahKickImg[10], "./img/Hannah/Kick/10.png");
	loadimage(&HannahKickImg[11], "./img/Hannah/Kick/11.png");

	//加载汉娜静止撩头发图像-方向向左
	loadimage(&HannahStillImgLeft[0], "./img/Hannah/StillPostureLeft/0.png");
	loadimage(&HannahStillImgLeft[1], "./img/Hannah/StillPostureLeft/1.png");
	loadimage(&HannahStillImgLeft[2], "./img/Hannah/StillPostureLeft/2.png");
	loadimage(&HannahStillImgLeft[3], "./img/Hannah/StillPostureLeft/3.png");

	//加载汉娜静止撩头发图像-方向向右
	loadimage(&HannahStillImgRight[0], "./img/Hannah/StillPostureRight/0.png");
	loadimage(&HannahStillImgRight[1], "./img/Hannah/StillPostureRight/1.png");
	loadimage(&HannahStillImgRight[2], "./img/Hannah/StillPostureRight/2.png");
	loadimage(&HannahStillImgRight[3], "./img/Hannah/StillPostureRight/3.png");

	//加载走路时的汉娜图像-方向向左
	loadimage(&HannahWalkImgLeft[0], "./img/Hannah/WalkLeft/0.png");
	loadimage(&HannahWalkImgLeft[1], "./img/Hannah/WalkLeft/1.png");
	loadimage(&HannahWalkImgLeft[2], "./img/Hannah/WalkLeft/2.png");
	loadimage(&HannahWalkImgLeft[3], "./img/Hannah/WalkLeft/3.png");
	loadimage(&HannahWalkImgLeft[4], "./img/Hannah/WalkLeft/4.png");
	loadimage(&HannahWalkImgLeft[5], "./img/Hannah/WalkLeft/5.png");
	loadimage(&HannahWalkImgLeft[6], "./img/Hannah/WalkLeft/6.png");
	loadimage(&HannahWalkImgLeft[7], "./img/Hannah/WalkLeft/7.png");
	loadimage(&HannahWalkImgLeft[8], "./img/Hannah/WalkLeft/8.png");
	loadimage(&HannahWalkImgLeft[9], "./img/Hannah/WalkLeft/9.png");
	loadimage(&HannahWalkImgLeft[10], "./img/Hannah/WalkLeft/10.png");
	loadimage(&HannahWalkImgLeft[11], "./img/Hannah/WalkLeft/11.png");

	//加载走路时的汉娜图像-方向向右
	loadimage(&HannahWalkImgRight[0], "./img/Hannah/WalkRight/0.png");
	loadimage(&HannahWalkImgRight[1], "./img/Hannah/WalkRight/1.png");
	loadimage(&HannahWalkImgRight[2], "./img/Hannah/WalkRight/2.png");
	loadimage(&HannahWalkImgRight[3], "./img/Hannah/WalkRight/3.png");
	loadimage(&HannahWalkImgRight[4], "./img/Hannah/WalkRight/4.png");
	loadimage(&HannahWalkImgRight[5], "./img/Hannah/WalkRight/5.png");
	loadimage(&HannahWalkImgRight[6], "./img/Hannah/WalkRight/6.png");
	loadimage(&HannahWalkImgRight[7], "./img/Hannah/WalkRight/7.png");
	loadimage(&HannahWalkImgRight[8], "./img/Hannah/WalkRight/8.png");
	loadimage(&HannahWalkImgRight[9], "./img/Hannah/WalkRight/9.png");
	loadimage(&HannahWalkImgRight[10], "./img/Hannah/WalkRight/10.png");
	loadimage(&HannahWalkImgRight[11], "./img/Hannah/WalkRight/11.png");

	//加载跑步时的汉娜图像-方向向左
	loadimage(&HannahRunImgLeft[0], "./img/Hannah/RunLeft/0.png");
	loadimage(&HannahRunImgLeft[1], "./img/Hannah/RunLeft/1.png");
	loadimage(&HannahRunImgLeft[2], "./img/Hannah/RunLeft/2.png");
	loadimage(&HannahRunImgLeft[3], "./img/Hannah/RunLeft/3.png");
	loadimage(&HannahRunImgLeft[4], "./img/Hannah/RunLeft/4.png");
	loadimage(&HannahRunImgLeft[5], "./img/Hannah/RunLeft/5.png");
	loadimage(&HannahRunImgLeft[6], "./img/Hannah/RunLeft/6.png");
	loadimage(&HannahRunImgLeft[7], "./img/Hannah/RunLeft/7.png");
	loadimage(&HannahRunImgLeft[8], "./img/Hannah/RunLeft/8.png");

	//加载跑步时的汉娜图像-方向向右
	loadimage(&HannahRunImgRight[0], "./img/Hannah/RunRight/0.png");
	loadimage(&HannahRunImgRight[1], "./img/Hannah/RunRight/1.png");
	loadimage(&HannahRunImgRight[2], "./img/Hannah/RunRight/2.png");
	loadimage(&HannahRunImgRight[3], "./img/Hannah/RunRight/3.png");
	loadimage(&HannahRunImgRight[4], "./img/Hannah/RunRight/4.png");
	loadimage(&HannahRunImgRight[5], "./img/Hannah/RunRight/5.png");
	loadimage(&HannahRunImgRight[6], "./img/Hannah/RunRight/6.png");
	loadimage(&HannahRunImgRight[7], "./img/Hannah/RunRight/7.png");
	loadimage(&HannahRunImgRight[8], "./img/Hannah/RunRight/8.png");

	//加载攻击时的汉娜图像-方向向左
	loadimage(&HannahAttackImgLeft[0], "./img/Hannah/AttackLeft/0.png");
	loadimage(&HannahAttackImgLeft[1], "./img/Hannah/AttackLeft/1.png");
	loadimage(&HannahAttackImgLeft[2], "./img/Hannah/AttackLeft/2.png");
	loadimage(&HannahAttackImgLeft[3], "./img/Hannah/AttackLeft/3.png");
	loadimage(&HannahAttackImgLeft[4], "./img/Hannah/AttackLeft/4.png");
	loadimage(&HannahAttackImgLeft[5], "./img/Hannah/AttackLeft/5.png");
	loadimage(&HannahAttackImgLeft[6], "./img/Hannah/AttackLeft/6.png");
	loadimage(&HannahAttackImgLeft[7], "./img/Hannah/AttackLeft/7.png");

	//加载攻击时的汉娜图像-方向向右
	loadimage(&HannahAttackImgRight[0], "./img/Hannah/AttackRight/0.png");
	loadimage(&HannahAttackImgRight[1], "./img/Hannah/AttackRight/1.png");
	loadimage(&HannahAttackImgRight[2], "./img/Hannah/AttackRight/2.png");
	loadimage(&HannahAttackImgRight[3], "./img/Hannah/AttackRight/3.png");
	loadimage(&HannahAttackImgRight[4], "./img/Hannah/AttackRight/4.png");
	loadimage(&HannahAttackImgRight[5], "./img/Hannah/AttackRight/5.png");
	loadimage(&HannahAttackImgRight[6], "./img/Hannah/AttackRight/6.png");
	loadimage(&HannahAttackImgRight[7], "./img/Hannah/AttackRight/7.png");

	//加载汉娜被击倒时的图像-方向向左
	loadimage(&HannahWasKnockedDownImgLeft[0], "./img/Hannah/WasKnockedDownLeft/0.png");
	loadimage(&HannahWasKnockedDownImgLeft[1], "./img/Hannah/WasKnockedDownLeft/1.png");
	loadimage(&HannahWasKnockedDownImgLeft[2], "./img/Hannah/WasKnockedDownLeft/2.png");
	loadimage(&HannahWasKnockedDownImgLeft[3], "./img/Hannah/WasKnockedDownLeft/3.png");
	loadimage(&HannahWasKnockedDownImgLeft[4], "./img/Hannah/WasKnockedDownLeft/4.png");
	loadimage(&HannahWasKnockedDownImgLeft[5], "./img/Hannah/WasKnockedDownLeft/5.png");

	//加载汉娜被击倒时的图像-方向向右
	loadimage(&HannahWasKnockedDownImgRight[0], "./img/Hannah/WasKnockedDownRight/0.png");
	loadimage(&HannahWasKnockedDownImgRight[1], "./img/Hannah/WasKnockedDownRight/1.png");
	loadimage(&HannahWasKnockedDownImgRight[2], "./img/Hannah/WasKnockedDownRight/2.png");
	loadimage(&HannahWasKnockedDownImgRight[3], "./img/Hannah/WasKnockedDownRight/3.png");
	loadimage(&HannahWasKnockedDownImgRight[4], "./img/Hannah/WasKnockedDownRight/4.png");
	loadimage(&HannahWasKnockedDownImgRight[5], "./img/Hannah/WasKnockedDownRight/5.png");

	//记载汉娜胜利图像-方向向左
	loadimage(&HannahVictoryImgLeft[0], "./img/Hannah/VictoryLeft/0.png");
	loadimage(&HannahVictoryImgLeft[1], "./img/Hannah/VictoryLeft/1.png");
	loadimage(&HannahVictoryImgLeft[2], "./img/Hannah/VictoryLeft/2.png");
	loadimage(&HannahVictoryImgLeft[3], "./img/Hannah/VictoryLeft/3.png");
	loadimage(&HannahVictoryImgLeft[4], "./img/Hannah/VictoryLeft/4.png");

	//记载汉娜胜利图像-方向向右
	loadimage(&HannahVictoryImgRight[0], "./img/Hannah/VictoryRight/0.png");
	loadimage(&HannahVictoryImgRight[1], "./img/Hannah/VictoryRight/1.png");
	loadimage(&HannahVictoryImgRight[2], "./img/Hannah/VictoryRight/2.png");
	loadimage(&HannahVictoryImgRight[3], "./img/Hannah/VictoryRight/3.png");
	loadimage(&HannahVictoryImgRight[4], "./img/Hannah/VictoryRight/4.png");


	Hannah.px = 1800;
	Hannah.py = 400;//320-450
	Hannah.vx = 17;
	Hannah.vy = 10;
	Hannah.status = DefensivePosture;
	Hannah.HorizontalDirection = right;
	Hannah.VerticalDirection = none;
	Hannah.life = 40000;
	Hannah.IsDead = false;

	//加载小怪A防御姿态的图像-方向向左
	loadimage(&EnemyADefensiveImgLeft, "./img/SmallEnemyA/DefensivePostureLeft/0.png");

	//加载小怪A防御姿态的图像-方向向右
	loadimage(&EnemyADefensiveImgRight, "./img/SmallEnemyA/DefensivePostureRight/0.png");

	//加载小怪A被击倒的图像-方向向左
	loadimage(&EnemyAWasKnockedDownImgLeft[0], "./img/SmallEnemyA/WasKnockedDownLeft/0.png");
	loadimage(&EnemyAWasKnockedDownImgLeft[1], "./img/SmallEnemyA/WasKnockedDownLeft/1.png");
	loadimage(&EnemyAWasKnockedDownImgLeft[2], "./img/SmallEnemyA/WasKnockedDownLeft/2.png");
	loadimage(&EnemyAWasKnockedDownImgLeft[3], "./img/SmallEnemyA/WasKnockedDownLeft/3.png");
	loadimage(&EnemyAWasKnockedDownImgLeft[4], "./img/SmallEnemyA/WasKnockedDownLeft/4.png");

	//加载小怪A被击倒的图像-方向向右
	loadimage(&EnemyAWasKnockedDownImgRight[0], "./img/SmallEnemyA/WasKnockedDownRight/0.png");
	loadimage(&EnemyAWasKnockedDownImgRight[1], "./img/SmallEnemyA/WasKnockedDownRight/1.png");
	loadimage(&EnemyAWasKnockedDownImgRight[2], "./img/SmallEnemyA/WasKnockedDownRight/2.png");
	loadimage(&EnemyAWasKnockedDownImgRight[3], "./img/SmallEnemyA/WasKnockedDownRight/3.png");
	loadimage(&EnemyAWasKnockedDownImgRight[4], "./img/SmallEnemyA/WasKnockedDownRight/4.png");

	//加载小怪A走路的图像-方向向左
	loadimage(&EnemyAWalkImgLeft[0], "./img/SmallEnemyA/WalkLeft/0.png");
	loadimage(&EnemyAWalkImgLeft[1], "./img/SmallEnemyA/WalkLeft/1.png");
	loadimage(&EnemyAWalkImgLeft[2], "./img/SmallEnemyA/WalkLeft/2.png");
	loadimage(&EnemyAWalkImgLeft[3], "./img/SmallEnemyA/WalkLeft/3.png");
	loadimage(&EnemyAWalkImgLeft[4], "./img/SmallEnemyA/WalkLeft/4.png");
	loadimage(&EnemyAWalkImgLeft[5], "./img/SmallEnemyA/WalkLeft/5.png");
	loadimage(&EnemyAWalkImgLeft[6], "./img/SmallEnemyA/WalkLeft/6.png");

	//加载小怪A走路的图像-方向向右
	loadimage(&EnemyAWalkImgRight[0], "./img/SmallEnemyA/WalkRight/0.png");
	loadimage(&EnemyAWalkImgRight[1], "./img/SmallEnemyA/WalkRight/1.png");
	loadimage(&EnemyAWalkImgRight[2], "./img/SmallEnemyA/WalkRight/2.png");
	loadimage(&EnemyAWalkImgRight[3], "./img/SmallEnemyA/WalkRight/3.png");
	loadimage(&EnemyAWalkImgRight[4], "./img/SmallEnemyA/WalkRight/4.png");
	loadimage(&EnemyAWalkImgRight[5], "./img/SmallEnemyA/WalkRight/5.png");
	loadimage(&EnemyAWalkImgRight[6], "./img/SmallEnemyA/WalkRight/6.png");

	//加载小怪A攻击时的图像-方向向左
	loadimage(&EnemyAAttackImgLeft[0], "./img/SmallEnemyA/AttackLeft/0.png");
	loadimage(&EnemyAAttackImgLeft[1], "./img/SmallEnemyA/AttackLeft/1.png");
	loadimage(&EnemyAAttackImgLeft[2], "./img/SmallEnemyA/AttackLeft/2.png");
	loadimage(&EnemyAAttackImgLeft[3], "./img/SmallEnemyA/AttackLeft/3.png");
	loadimage(&EnemyAAttackImgLeft[4], "./img/SmallEnemyA/AttackLeft/4.png");
	loadimage(&EnemyAAttackImgLeft[5], "./img/SmallEnemyA/AttackLeft/5.png");
	loadimage(&EnemyAAttackImgLeft[6], "./img/SmallEnemyA/AttackLeft/6.png");
	loadimage(&EnemyAAttackImgLeft[7], "./img/SmallEnemyA/AttackLeft/7.png");
	loadimage(&EnemyAAttackImgLeft[8], "./img/SmallEnemyA/AttackLeft/8.png");

	//加载小怪A攻击时的图像-方向向右
	loadimage(&EnemyAAttackImgRight[0], "./img/SmallEnemyA/AttackRight/0.png");
	loadimage(&EnemyAAttackImgRight[1], "./img/SmallEnemyA/AttackRight/1.png");
	loadimage(&EnemyAAttackImgRight[2], "./img/SmallEnemyA/AttackRight/2.png");
	loadimage(&EnemyAAttackImgRight[3], "./img/SmallEnemyA/AttackRight/3.png");
	loadimage(&EnemyAAttackImgRight[4], "./img/SmallEnemyA/AttackRight/4.png");
	loadimage(&EnemyAAttackImgRight[5], "./img/SmallEnemyA/AttackRight/5.png");
	loadimage(&EnemyAAttackImgRight[6], "./img/SmallEnemyA/AttackRight/6.png");
	loadimage(&EnemyAAttackImgRight[7], "./img/SmallEnemyA/AttackRight/7.png");
	loadimage(&EnemyAAttackImgRight[8], "./img/SmallEnemyA/AttackRight/8.png");

	//加载小怪A静止时的图像-方向向左
	loadimage(&EnemyAStillImgLeft[0], "./img/SmallEnemyA/StillLeft/0.png");
	loadimage(&EnemyAStillImgLeft[1], "./img/SmallEnemyA/StillLeft/1.png");
	loadimage(&EnemyAStillImgLeft[2], "./img/SmallEnemyA/StillLeft/2.png");

	//加载小怪A静止时的图像-方向向右
	loadimage(&EnemyAStillImgRight[0], "./img/SmallEnemyA/StillRight/0.png");
	loadimage(&EnemyAStillImgRight[1], "./img/SmallEnemyA/StillRight/1.png");
	loadimage(&EnemyAStillImgRight[2], "./img/SmallEnemyA/StillRight/2.png");

	//加载小怪A特殊图片
	loadimage(&EnemyASpecialImg[0], "./img/SmallEnemyA/SpecialPosture/0.png");
	loadimage(&EnemyASpecialImg[1], "./img/SmallEnemyA/SpecialPosture/1.png");
	loadimage(&EnemyASpecialImg[2], "./img/SmallEnemyA/SpecialPosture/2.png");


	EnemyA.px = 230;
	EnemyA.py = 400;
	EnemyA.vx = 20;
	EnemyA.vy = 15;
	EnemyA.status = DefensivePosture;
	EnemyA.HorizontalDirection = right;
	EnemyA.WasAttackCnt = 0;
	EnemyA.IsDead = false;
	EnemyA.life = 10000;
	EnemyA.BeginTime = 0;
	EnemyA.ElapsedTime = 2500;
	EnemyA.IsShouldRest = false;
	EnemyA.IsSpecialPosture = false;




	//加载小怪B防御姿态的图像-方向向左
	loadimage(&EnemyBDefensiveImgLeft, "./img/SmallEnemyB/DefensivePostureLeft/0.png");
	//加载小怪B防御姿态的图像-方向向右
	loadimage(&EnemyBDefensiveImgRight, "./img/SmallEnemyB/DefensivePostureRight/0.png");

	//加载小怪B被击倒的图像-方向向左
	loadimage(&EnemyBWasKnockedDownImgLeft[0], "./img/SmallEnemyB/WasKnockedDownLeft/0.png");
	loadimage(&EnemyBWasKnockedDownImgLeft[1], "./img/SmallEnemyB/WasKnockedDownLeft/1.png");
	loadimage(&EnemyBWasKnockedDownImgLeft[2], "./img/SmallEnemyB/WasKnockedDownLeft/2.png");
	loadimage(&EnemyBWasKnockedDownImgLeft[3], "./img/SmallEnemyB/WasKnockedDownLeft/3.png");
	loadimage(&EnemyBWasKnockedDownImgLeft[4], "./img/SmallEnemyB/WasKnockedDownLeft/4.png");

	//加载小怪B被击倒的图像-方向向右
	loadimage(&EnemyBWasKnockedDownImgRight[0], "./img/SmallEnemyB/WasKnockedDownRight/0.png");
	loadimage(&EnemyBWasKnockedDownImgRight[1], "./img/SmallEnemyB/WasKnockedDownRight/1.png");
	loadimage(&EnemyBWasKnockedDownImgRight[2], "./img/SmallEnemyB/WasKnockedDownRight/2.png");
	loadimage(&EnemyBWasKnockedDownImgRight[3], "./img/SmallEnemyB/WasKnockedDownRight/3.png");
	loadimage(&EnemyBWasKnockedDownImgRight[4], "./img/SmallEnemyB/WasKnockedDownRight/4.png");

	//加载小怪B走路的图像-方向向左
	loadimage(&EnemyBWalkImgLeft[0], "./img/SmallEnemyB/WalkLeft/0.png");
	loadimage(&EnemyBWalkImgLeft[1], "./img/SmallEnemyB/WalkLeft/1.png");
	loadimage(&EnemyBWalkImgLeft[2], "./img/SmallEnemyB/WalkLeft/2.png");
	loadimage(&EnemyBWalkImgLeft[3], "./img/SmallEnemyB/WalkLeft/3.png");
	loadimage(&EnemyBWalkImgLeft[4], "./img/SmallEnemyB/WalkLeft/4.png");
	loadimage(&EnemyBWalkImgLeft[5], "./img/SmallEnemyB/WalkLeft/5.png");
	loadimage(&EnemyBWalkImgLeft[6], "./img/SmallEnemyB/WalkLeft/6.png");

	//加载小怪B走路的图像-方向向右
	loadimage(&EnemyBWalkImgRight[0], "./img/SmallEnemyB/WalkRight/0.png");
	loadimage(&EnemyBWalkImgRight[1], "./img/SmallEnemyB/WalkRight/1.png");
	loadimage(&EnemyBWalkImgRight[2], "./img/SmallEnemyB/WalkRight/2.png");
	loadimage(&EnemyBWalkImgRight[3], "./img/SmallEnemyB/WalkRight/3.png");
	loadimage(&EnemyBWalkImgRight[4], "./img/SmallEnemyB/WalkRight/4.png");
	loadimage(&EnemyBWalkImgRight[5], "./img/SmallEnemyB/WalkRight/5.png");
	loadimage(&EnemyBWalkImgRight[6], "./img/SmallEnemyB/WalkRight/6.png");

	//加载小怪B攻击时的图像-方向向左
	loadimage(&EnemyBAttackImgLeft[0], "./img/SmallEnemyB/AttackLeft/0.png");
	loadimage(&EnemyBAttackImgLeft[1], "./img/SmallEnemyB/AttackLeft/1.png");
	loadimage(&EnemyBAttackImgLeft[2], "./img/SmallEnemyB/AttackLeft/2.png");
	loadimage(&EnemyBAttackImgLeft[3], "./img/SmallEnemyB/AttackLeft/3.png");
	loadimage(&EnemyBAttackImgLeft[4], "./img/SmallEnemyB/AttackLeft/4.png");
	loadimage(&EnemyBAttackImgLeft[5], "./img/SmallEnemyB/AttackLeft/5.png");
	loadimage(&EnemyBAttackImgLeft[6], "./img/SmallEnemyB/AttackLeft/6.png");
	loadimage(&EnemyBAttackImgLeft[7], "./img/SmallEnemyB/AttackLeft/7.png");
	loadimage(&EnemyBAttackImgLeft[8], "./img/SmallEnemyB/AttackLeft/8.png");

	//加载小怪B攻击时的图像-方向向右
	loadimage(&EnemyBAttackImgRight[0], "./img/SmallEnemyB/AttackRight/0.png");
	loadimage(&EnemyBAttackImgRight[1], "./img/SmallEnemyB/AttackRight/1.png");
	loadimage(&EnemyBAttackImgRight[2], "./img/SmallEnemyB/AttackRight/2.png");
	loadimage(&EnemyBAttackImgRight[3], "./img/SmallEnemyB/AttackRight/3.png");
	loadimage(&EnemyBAttackImgRight[4], "./img/SmallEnemyB/AttackRight/4.png");
	loadimage(&EnemyBAttackImgRight[5], "./img/SmallEnemyB/AttackRight/5.png");
	loadimage(&EnemyBAttackImgRight[6], "./img/SmallEnemyB/AttackRight/6.png");
	loadimage(&EnemyBAttackImgRight[7], "./img/SmallEnemyB/AttackRight/7.png");
	loadimage(&EnemyBAttackImgRight[8], "./img/SmallEnemyB/AttackRight/8.png");

	//加载小怪B静止时的图像-方向向左
	loadimage(&EnemyBStillImgLeft[0], "./img/SmallEnemyB/StillLeft/0.png");
	loadimage(&EnemyBStillImgLeft[1], "./img/SmallEnemyB/StillLeft/1.png");
	loadimage(&EnemyBStillImgLeft[2], "./img/SmallEnemyB/StillLeft/2.png");

	//加载小怪B静止时的图像-方向向右
	loadimage(&EnemyBStillImgRight[0], "./img/SmallEnemyB/StillRight/0.png");
	loadimage(&EnemyBStillImgRight[1], "./img/SmallEnemyB/StillRight/1.png");
	loadimage(&EnemyBStillImgRight[2], "./img/SmallEnemyB/StillRight/2.png");

	EnemyB.px = 800;
	EnemyB.py = 400;
	EnemyB.vx = 15;
	EnemyB.vy = 10;
	EnemyB.status = DefensivePosture;
	EnemyB.HorizontalDirection = left;
	EnemyB.WasAttackCnt = 0;
	EnemyB.IsDead = false;
	EnemyB.life = 10000;
	EnemyB.BeginTime = 0;
	EnemyB.ElapsedTime = 2500;
	EnemyB.IsShouldRest = false;


	//加载小怪C防御姿态的图像-方向向左
	loadimage(&EnemyCDefensiveImgLeft, "./img/SmallEnemyC/DefensivePostureLeft/0.png");
	//加载小怪C防御姿态的图像-方向向右
	loadimage(&EnemyCDefensiveImgRight, "./img/SmallEnemyC/DefensivePostureRight/0.png");

	//加载小怪C被击倒的图像-方向向左
	loadimage(&EnemyCWasKnockedDownImgLeft[0], "./img/SmallEnemyC/WasKnockedDownLeft/0.png");
	loadimage(&EnemyCWasKnockedDownImgLeft[1], "./img/SmallEnemyC/WasKnockedDownLeft/1.png");
	loadimage(&EnemyCWasKnockedDownImgLeft[2], "./img/SmallEnemyC/WasKnockedDownLeft/2.png");
	loadimage(&EnemyCWasKnockedDownImgLeft[3], "./img/SmallEnemyC/WasKnockedDownLeft/3.png");
	loadimage(&EnemyCWasKnockedDownImgLeft[4], "./img/SmallEnemyC/WasKnockedDownLeft/4.png");

	//加载小怪C被击倒的图像-方向向右
	loadimage(&EnemyCWasKnockedDownImgRight[0], "./img/SmallEnemyC/WasKnockedDownRight/0.png");
	loadimage(&EnemyCWasKnockedDownImgRight[1], "./img/SmallEnemyC/WasKnockedDownRight/1.png");
	loadimage(&EnemyCWasKnockedDownImgRight[2], "./img/SmallEnemyC/WasKnockedDownRight/2.png");
	loadimage(&EnemyCWasKnockedDownImgRight[3], "./img/SmallEnemyC/WasKnockedDownRight/3.png");
	loadimage(&EnemyCWasKnockedDownImgRight[4], "./img/SmallEnemyC/WasKnockedDownRight/4.png");

	//加载小怪C走路的图像-方向向左
	loadimage(&EnemyCWalkImgLeft[0], "./img/SmallEnemyC/WalkLeft/0.png");
	loadimage(&EnemyCWalkImgLeft[1], "./img/SmallEnemyC/WalkLeft/1.png");
	loadimage(&EnemyCWalkImgLeft[2], "./img/SmallEnemyC/WalkLeft/2.png");
	loadimage(&EnemyCWalkImgLeft[3], "./img/SmallEnemyC/WalkLeft/3.png");
	loadimage(&EnemyCWalkImgLeft[4], "./img/SmallEnemyC/WalkLeft/4.png");

	//加载小怪C走路的图像-方向向右
	loadimage(&EnemyCWalkImgRight[0], "./img/SmallEnemyC/WalkRight/0.png");
	loadimage(&EnemyCWalkImgRight[1], "./img/SmallEnemyC/WalkRight/1.png");
	loadimage(&EnemyCWalkImgRight[2], "./img/SmallEnemyC/WalkRight/2.png");
	loadimage(&EnemyCWalkImgRight[3], "./img/SmallEnemyC/WalkRight/3.png");
	loadimage(&EnemyCWalkImgRight[4], "./img/SmallEnemyC/WalkRight/4.png");

	//加载小怪C冲撞的图片-方向向左
	loadimage(&EnemyCCollideImgLeft[0], "./img/SmallEnemyC/CollideLeft/0.png");
	loadimage(&EnemyCCollideImgLeft[1], "./img/SmallEnemyC/CollideLeft/1.png");
	loadimage(&EnemyCCollideImgLeft[2], "./img/SmallEnemyC/CollideLeft/2.png");
	loadimage(&EnemyCCollideImgLeft[3], "./img/SmallEnemyC/CollideLeft/3.png");
	loadimage(&EnemyCCollideImgLeft[4], "./img/SmallEnemyC/CollideLeft/4.png");
	loadimage(&EnemyCCollideImgLeft[5], "./img/SmallEnemyC/CollideLeft/5.png");

	//加载小怪C冲撞的图片-方向向右
	loadimage(&EnemyCCollideImgRight[0], "./img/SmallEnemyC/CollideRight/0.png");
	loadimage(&EnemyCCollideImgRight[1], "./img/SmallEnemyC/CollideRight/1.png");
	loadimage(&EnemyCCollideImgRight[2], "./img/SmallEnemyC/CollideRight/2.png");
	loadimage(&EnemyCCollideImgRight[3], "./img/SmallEnemyC/CollideRight/3.png");
	loadimage(&EnemyCCollideImgRight[4], "./img/SmallEnemyC/CollideRight/4.png");
	loadimage(&EnemyCCollideImgRight[5], "./img/SmallEnemyC/CollideRight/5.png");


	//加载小怪C静止时的图像-方向向左
	loadimage(&EnemyCStillImgLeft[0], "./img/SmallEnemyC/StillLeft/0.png");
	loadimage(&EnemyCStillImgLeft[1], "./img/SmallEnemyC/StillLeft/1.png");
	loadimage(&EnemyCStillImgLeft[2], "./img/SmallEnemyC/StillLeft/2.png");
	loadimage(&EnemyCStillImgLeft[3], "./img/SmallEnemyC/StillLeft/3.png");
	loadimage(&EnemyCStillImgLeft[4], "./img/SmallEnemyC/StillLeft/4.png");
	loadimage(&EnemyCStillImgLeft[5], "./img/SmallEnemyC/StillLeft/5.png");
	loadimage(&EnemyCStillImgLeft[6], "./img/SmallEnemyC/StillLeft/6.png");
	loadimage(&EnemyCStillImgLeft[7], "./img/SmallEnemyC/StillLeft/7.png");
	loadimage(&EnemyCStillImgLeft[8], "./img/SmallEnemyC/StillLeft/8.png");

	//加载小怪C静止时的图像-方向向右
	loadimage(&EnemyCStillImgRight[0], "./img/SmallEnemyC/StillRight/0.png");
	loadimage(&EnemyCStillImgRight[1], "./img/SmallEnemyC/StillRight/1.png");
	loadimage(&EnemyCStillImgRight[2], "./img/SmallEnemyC/StillRight/2.png");
	loadimage(&EnemyCStillImgRight[3], "./img/SmallEnemyC/StillRight/3.png");
	loadimage(&EnemyCStillImgRight[4], "./img/SmallEnemyC/StillRight/4.png");
	loadimage(&EnemyCStillImgRight[5], "./img/SmallEnemyC/StillRight/5.png");
	loadimage(&EnemyCStillImgRight[6], "./img/SmallEnemyC/StillRight/6.png");
	loadimage(&EnemyCStillImgRight[7], "./img/SmallEnemyC/StillRight/7.png");
	loadimage(&EnemyCStillImgRight[8], "./img/SmallEnemyC/StillRight/8.png");

	EnemyC.px = 50;
	EnemyC.py = 320;
	EnemyC.vx = 50;
	EnemyC.distance = 0;
	EnemyC.vy = 20;
	EnemyC.status = TrackPosture;
	EnemyC.HorizontalDirection = right;
	EnemyC.life = 100000;



}

void StartMenuShow()
{
	if (GameStatus == StartMenu)
	{
		static int StartMenuCnt = 0;
		static DWORD StartMenuBeginTime = 0;
		DWORD StartMenuElapsedTime = 2000;

		if (!StartMenuBeginTime)
			StartMenuBeginTime = GetTickCount();
		transparentimage(NULL, 0, 0, &StartMenuImg[StartMenuCnt]);

		if (GetTickCount() - StartMenuBeginTime >= StartMenuElapsedTime)
		{
			StartMenuCnt++;
			if (StartMenuCnt > 3)
			{
				StartMenuCnt = 0;
				GameStatus = FirstStageFirstCutscene;
			}
			StartMenuBeginTime = 0;
		}
	}
}

void BackGroundShow()
{
	if (GameStatus == FirstStage || GameStatus == FirstStageFirstCutscene || GameStatus == FirstStageSecondCutscene || GameStatus == FirstStageThirdCutscene)
		transparentimage(NULL, FirstStageFirst.px, FirstStageFirst.py, &FirstStageBackgroundImg[0]);
	else if (GameStatus == FirstStageFourthCutscene)
		transparentimage(NULL, FirstStageFirst.px, FirstStageFirst.py, &FirstStageBackgroundImg[1]);
	else if (GameStatus == SecondStage || GameStatus==SecondStageSecondCutscene || GameStatus == ThirdStage)
		transparentimage(NULL, SecondStageFirst.px, SecondStageFirst.py, &SecondStageBackGroundImg[3]);
}

void GameStatusChange()
{
	if (EnemyA.flag == FirstStageEnd && EnemyB.flag == FirstStageEnd && GameStatus == FirstStage)
	{
		GameStatus = FirstStageThirdCutscene;
		Hannah.px = 350;
		Hannah.py = 400;
	}
	else if (GameStatus == SecondStage && EnemyA.flag == FirstStageEnd && EnemyB.flag == FirstStageEnd)
	{
		GameStatus = SecondStageSecondCutscene;
	}
}


void HannahInformationShow()
{
	transparentimage(NULL, HannahAvatar.px, HannahAvatar.py, &HannahAvatarImg);

	if (GameStatus != FirstStageFirstCutscene &&GameStatus!=StartMenu)
	{
		setlinecolor(RGB(255, 255, 255));
		setlinestyle(PS_SOLID, 2);
		setfillstyle(BS_SOLID);
		setfillcolor(RGB(255, 255, 0));
		double bloodx = (double)Hannah.life / 40000 * 280 + 120;
		if (bloodx <= 120)
			bloodx = 120;
		fillrectangle(120, 80, bloodx, 110);

		setlinecolor(RGB(255, 255, 255));
		setlinestyle(PS_SOLID, 3);
		setfillstyle(BS_NULL);
		fillrectangle(120, 80, 400, 110);
	}
}

void EnemyAInformationShow()
{
	if (GameStatus == FirstStage || GameStatus == FirstStageFirstCutscene || GameStatus == FirstStageSecondCutscene || GameStatus == SecondStage || GameStatus == SecondStageFirstCutscene)
	{
		transparentimage(NULL, EnemyAAvatar.px, EnemyAAvatar.py, &EnemyAAvatarImg);

		if (GameStatus != FirstStageFirstCutscene)
		{
			setlinecolor(RGB(255, 255, 255));
			setlinestyle(PS_SOLID, 3);

			setfillstyle(BS_SOLID);
			setfillcolor(RGB(255, 0, 0));
			setfillstyle(BS_SOLID);
			fillrectangle(70, 140, 300, 160);

			setfillcolor(RGB(255, 255, 0));
			double bloodx = EnemyA.life / 10000 * 230 + 70;
			if (bloodx <= 70)
				bloodx = 70;
			fillrectangle(70, 140, bloodx, 160);
		}
	}
}

void EnemyBInformationShow()
{
	if (GameStatus == FirstStage || GameStatus == FirstStageFirstCutscene || GameStatus == FirstStageSecondCutscene || GameStatus == SecondStage || GameStatus == SecondStageFirstCutscene)
	{
		transparentimage(NULL, EnemyBAvatar.px, EnemyBAvatar.py, &EnemyBAvatarImg);

		if (GameStatus != FirstStageFirstCutscene)
		{
			setfillstyle(BS_SOLID);
			setfillcolor(RGB(255, 0, 0));
			setfillstyle(BS_SOLID);
			fillrectangle(70, 190, 300, 210);

			setfillcolor(RGB(255, 255, 0));
			double bloodx = EnemyB.life / 10000 * 230 + 70;
			if (bloodx <= 70)
				bloodx = 70;
			fillrectangle(70, 190, bloodx, 210);
		}
	}
}

void EnemyCInformationShow()
{
	transparentimage(NULL,EnemyCAvatar.px,EnemyCAvatar.py, &EnemyCAvatarImg);

	if (GameStatus == ThirdStage)
	{
		setfillstyle(BS_SOLID);
		setfillcolor(RGB(255, 0, 0));
		setfillstyle(BS_SOLID);
		fillrectangle(100, 120, 800, 170);

		setfillcolor(RGB(255, 255, 0));
		double bloodx = EnemyC.life / 100000 * 700 + 100;
		if (bloodx <= 120)
			bloodx = 100;
		fillrectangle(100, 120, bloodx, 170);
	}
}

void DropShow()
{
	if (GameStatus == FirstStage || GameStatus==SecondStage)
	{
		if (Food.status == 0)
			transparentimage(NULL, Food.px, Food.py, &FoodImg[Food.status]);

		else if (Food.status == 1)
			transparentimage(NULL, Food.px, Food.py, &FoodImg[Food.status]);

		else if (Food.status == 2)
			transparentimage(NULL, Food.px, Food.py, &FoodImg[Food.status]);

		else if (Food.status == 3)
			transparentimage(NULL, Food.px, Food.py, &FoodImg[Food.status]);

		else if (Food.status == 4)
			transparentimage(NULL, Food.px, Food.py, &FoodImg[Food.status]);
	}
}

void FirstStageFirstCutsceneShow()
{
	if (GameStatus == FirstStageFirstCutscene)
	{
		if (FirstStageFirst.distance <= 1250)
		{
			FirstStageFirst.distance += FirstStageFirst.vx;
			FirstStageFirst.px -= FirstStageFirst.vx;
			Hannah.px -= FirstStageFirst.vx;
			FirstStageSecond.px -= FirstStageFirst.vx;

			HannahAvatar.px-=HannahAvatar.vx;
			EnemyAAvatar.px -= EnemyAAvatar.vx;
			EnemyBAvatar.px -= EnemyBAvatar.vx;

			static int cnt = 0;
			for (int i = 0; i < 2; i++)
			{
				if (!Pterosaur[0].BeginTime)
					Pterosaur[0].BeginTime = GetTickCount();
				Pterosaur[i].px += Pterosaur[i].vx;
				Pterosaur[i].py -= Pterosaur[i].vy;
				transparentimage(NULL, Pterosaur[i].px, Pterosaur[i].py, &PterosureImg[cnt]);
				if (i == 1 && GetTickCount() - Pterosaur[0].BeginTime >= Pterosaur[0].ElapsedTime)
				{
					cnt++;
					if (cnt > 4)
						cnt = 0;
					Pterosaur[0].BeginTime = GetTickCount();
				}
			}
		}
		else
			GameStatus = FirstStageSecondCutscene;
	}
}

void FirstStageSecondCutsceneShow()
{
	if (GameStatus == FirstStageFirstCutscene)
	{
		//输出汉娜过场动画图像
		transparentimage(NULL, Hannah.px, Hannah.py, &HannahDefensiveImgRight);

		//输出小怪A过场动画图像
		transparentimage(NULL, FirstStageSecond.px - 50, FirstStageSecond.py, &EnemyADefensiveImgRight);
		transparentimage(NULL, FirstStageSecond.px, FirstStageSecond.py + 70, &EnemyADefensiveImgRight);
		transparentimage(NULL, FirstStageSecond.px - 50, FirstStageSecond.py + 140, &EnemyADefensiveImgRight);

		//输出小怪B过场动画图像
		transparentimage(NULL, FirstStageSecond.px + 360, FirstStageSecond.py, &EnemyBDefensiveImgLeft);
		transparentimage(NULL, FirstStageSecond.px + 300, FirstStageSecond.py + 70, &EnemyBDefensiveImgLeft);
		transparentimage(NULL, FirstStageSecond.px + 360, FirstStageSecond.py + 140, &EnemyBDefensiveImgLeft);
	}

	if (GameStatus == FirstStageSecondCutscene)
	{
		static bool IsAnimationEnd = false;
		static int cnt = 0;
		static int i = 0;

		transparentimage(NULL, Hannah.px, Hannah.py, &HannahKickImg[cnt]);
		//输出小怪A过场动画图像
		transparentimage(NULL, FirstStageSecond.px - 50, FirstStageSecond.py, &EnemyAWasKnockedDownImgRight[i]);
		transparentimage(NULL, FirstStageSecond.px, FirstStageSecond.py + 70, &EnemyAWasKnockedDownImgRight[i]);
		transparentimage(NULL, FirstStageSecond.px - 50, FirstStageSecond.py + 140, &EnemyAWasKnockedDownImgRight[i]);

		//输出小怪B过场动画图像
		transparentimage(NULL, FirstStageSecond.px + 360, FirstStageSecond.py, &EnemyBWasKnockedDownImgLeft[i]);
		transparentimage(NULL, FirstStageSecond.px + 300, FirstStageSecond.py + 70, &EnemyBWasKnockedDownImgLeft[i]);
		transparentimage(NULL, FirstStageSecond.px + 360, FirstStageSecond.py + 140, &EnemyAWasKnockedDownImgLeft[i]);

		if (!IsAnimationEnd)
		{
			if (!FirstStageSecond.BeginTime)
				FirstStageSecond.BeginTime = GetTickCount();
			if (GetTickCount() - FirstStageSecond.BeginTime >= FirstStageSecond.ElapsedTime)
			{
				cnt++;
				if (cnt % 2 == 0 && cnt < 10)
				{
					i++;
					FirstStageSecond.py += 30;
					FirstStageSecond.px -= 30;
				}
				if (cnt > 10)
					IsAnimationEnd = true;
				FirstStageSecond.BeginTime = 0;
			}
		}
		else
		{
			GameStatus = FirstStage;
		}
	}

}

static int HannahAttackPostureFirstCnt = 0;
void FirstStageThirdCutsceneShow()
{
	if (GameStatus == FirstStageThirdCutscene || GameStatus==FirstStageFourthCutscene && !EnemyA.IsSpecialPosture )
	{
		if (FirstStageFirst.distance <= 5000)
		{
			FirstStageFirst.distance += FirstStageFirst.vx;
			FirstStageFirst.px -= FirstStageFirst.vx / 8;

			static int WalkPostureCnt = 0;
			static DWORD WalkPostureBeginTime = 0;
			static DWORD WalkPostureElapsedTime = 100;

			transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgRight[WalkPostureCnt]);
			if (!WalkPostureBeginTime)
				WalkPostureBeginTime = GetTickCount();
			if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
			{
				WalkPostureCnt++;
				Hannah.px += FirstStageFirst.vx*16;
				{
					if (WalkPostureCnt > 11)
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
					}
				}
				WalkPostureBeginTime = 0;
			}
		}

		if (FirstStageFirst.distance <= 7000 && FirstStageFirst.distance >= 5000)
		{
			FirstStageFirst.distance += FirstStageFirst.vx;
			FirstStageFirst.distance += FirstStageFirst.vx;
			FirstStageFirst.px -= FirstStageFirst.vx / 6;

			static int WalkPostureCnt = 0;
			static DWORD WalkPostureBeginTime = 0;
			static DWORD WalkPostureElapsedTime = 100;

			transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgRight[WalkPostureCnt]);
			if (!WalkPostureBeginTime)
				WalkPostureBeginTime = GetTickCount();
			if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
			{
				WalkPostureCnt++;
				Hannah.py += FirstStageFirst.vx * 10;
				{
					if (WalkPostureCnt > 11)
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
					}
				}
				WalkPostureBeginTime = 0;
			}
		}

		else if (FirstStageFirst.distance >= 7000 &&FirstStageFirst.distance<=7002)
		{
			static DWORD AttackPostureFirstBeginTime = 0;
			DWORD AttackPostureFirstElapsedTime = 250;

			transparentimage(NULL, Hannah.px, Hannah.py, &HannahAttackImgRight[HannahAttackPostureFirstCnt]);
			if (!AttackPostureFirstBeginTime)
				AttackPostureFirstBeginTime = GetTickCount();
			if (GetTickCount() - AttackPostureFirstBeginTime >= AttackPostureFirstElapsedTime)
			{
				HannahAttackPostureFirstCnt++;
				{
					if ((HannahAttackPostureFirstCnt > 1))
					{
						HannahAttackPostureFirstCnt = 0;
						FirstStageFirst.distance += 1;
						GameStatus = FirstStageFourthCutscene;
					}
				}
				AttackPostureFirstBeginTime = 0;
			}
		}

		else if (FirstStageFirst.distance >= 7002)
		{

			static int WalkPostureCnt = 0;
			static DWORD WalkPostureBeginTime = 0;
			static DWORD WalkPostureElapsedTime = 100;

			transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgRight[WalkPostureCnt]);
			if (!WalkPostureBeginTime)
				WalkPostureBeginTime = GetTickCount();
			if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
			{
				WalkPostureCnt++;
				Hannah.px += FirstStageFirst.vx*16;
				{
					if (WalkPostureCnt > 4)
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
						GameStatus = SecondStageFirstCutscene;


						Hannah.px = 200;
						Hannah.py = 350;
						cleardevice();
					}
				}
				WalkPostureBeginTime = 0;
			}
		}
	}
}

void SecondStageFirstCutsceneShow()
{
	if (GameStatus == SecondStageFirstCutscene)
	{
		static int SecondStageFirstCnt = 0;
		if (!SecondStageFirst.BeginTime)
			SecondStageFirst.BeginTime = GetTickCount();
		transparentimage(NULL, SecondStageFirst.px, SecondStageFirst.py, &SecondStageBackGroundImg[SecondStageFirstCnt]);
		if (GetTickCount() - SecondStageFirst.BeginTime >= SecondStageFirst.ElapsedTime)
		{
			SecondStageFirstCnt++;
			if (SecondStageFirstCnt > 3)
			{
				SecondStageFirstCnt = 0;
				GameStatus = SecondStage;
				EnemyA.IsSpecialPosture = true;

				EnemyA.px = 580;
				EnemyA.py = 270;
				EnemyA.flag = 0;
				EnemyA.life = 10000;
				EnemyA.status = DefensivePosture;

				EnemyB.px = 800;
				EnemyB.py = 400;
				EnemyB.flag= 0;
				EnemyB.life = 10000;
				EnemyB.status = DefensivePosture;

				Hannah.px = 200;
				Hannah.py = 500;//320-500
			}
			SecondStageFirst.BeginTime = 0;
		}
	}
}

void SecondStageEnemyASpecialPostureShow()
{
	if (GameStatus == SecondStage && EnemyA.IsSpecialPosture)
	{
		static int SpecialPostureCnt = 0;
		static DWORD SpecialPostureBeginTime = 0;
		DWORD SpecialPostureElapsedTime = 250;

		if (!SpecialPostureBeginTime)
			SpecialPostureBeginTime = GetTickCount();
		transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyASpecialImg[SpecialPostureCnt]);
		if (GetTickCount() - SpecialPostureBeginTime >= SpecialPostureElapsedTime)
		{
			SpecialPostureCnt++;
			EnemyA.py += 30;
			if (SpecialPostureCnt > 2)
			{
				SpecialPostureCnt = 0;
				EnemyA.IsSpecialPosture = false;
			}
			SpecialPostureBeginTime = 0;
		}
	}
}

void SecondStageSecondCutsceneShow()
{
	if (GameStatus == SecondStageSecondCutscene)
	{
		if (SecondStageFirst.distance <= 1160)
		{
			SecondStageFirst.distance += SecondStageFirst.vx;
			SecondStageFirst.px -= SecondStageFirst.vx;

			EnemyCAvatar.px -= EnemyCAvatar.vx;

			static int WalkPostureCnt = 0;
			static DWORD WalkPostureBeginTime = 0;
			static DWORD WalkPostureElapsedTime = 100;

			transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgRight[WalkPostureCnt]);

			if (!WalkPostureBeginTime)
				WalkPostureBeginTime = GetTickCount();
			if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
			{
				WalkPostureCnt++;
				Hannah.px += FirstStageFirst.vx;
				{
					if (WalkPostureCnt > 11)
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
					}
				}
				WalkPostureBeginTime = 0;
			}
		}

		else
		{
			GameStatus = ThirdStage;
			Hannah.status = DefensivePosture;
			EnemyA.flag = 0;
			EnemyB.flag = 0;
		}
	}
}


















static DWORD StillBeginTime = 0;
void HannahStatusChange()
{
	if (GameStatus == FirstStage || GameStatus == SecondStage || GameStatus == ThirdStage && Hannah.status!=VictoryPosture &&Hannah.status!=DeathPosture)
	{
		DWORD ElapsedTime = 2500;
		if (!GetAsyncKeyState('W') && !GetAsyncKeyState('S')
			&& !GetAsyncKeyState('A')
			&& !GetAsyncKeyState('D') && !GetAsyncKeyState('J')
			&& !GetAsyncKeyState('K'))
		{
			if (!StillBeginTime)
				StillBeginTime = GetTickCount();
			if (GetTickCount() - StillBeginTime >= ElapsedTime)
				Hannah.status = StillPosture;
		}

		//汉娜向上移动
		if (GetAsyncKeyState('W'))
		{
			Hannah.VerticalDirection = up;
			Hannah.status = WalkPosture;
			StillBeginTime = 0;
		}

		//汉娜向下移动
		if (GetAsyncKeyState('S'))
		{
			Hannah.VerticalDirection = down;
			Hannah.status = WalkPosture;
			StillBeginTime = 0;
		}

		//汉娜向左移动
		if (GetAsyncKeyState('A'))
		{
			Hannah.status = WalkPosture;
			Hannah.HorizontalDirection = left;
			Hannah.VerticalDirection = none;
			StillBeginTime = 0;
		}

		//汉娜向右移动
		if (GetAsyncKeyState('D'))
		{
			Hannah.status = WalkPosture;
			Hannah.HorizontalDirection = right;
			Hannah.VerticalDirection = none;
			StillBeginTime = 0;
		}

		//汉娜向上跑步
		if ((GetAsyncKeyState('W') & 0x8000) && ((GetAsyncKeyState(VK_SHIFT) & 0x8000)))
		{
			Hannah.status = RunPosture;
			Hannah.VerticalDirection = up;
			StillBeginTime = 0;
		}

		//汉娜向下跑步
		if ((GetAsyncKeyState('S') & 0x8000) && ((GetAsyncKeyState(VK_SHIFT) & 0x8000)))
		{
			Hannah.status = RunPosture;
			Hannah.VerticalDirection = down;
			StillBeginTime = 0;
		}

		//汉娜向左跑步
		if ((GetAsyncKeyState('A') & 0x8000) && ((GetAsyncKeyState(VK_SHIFT) & 0x8000)))
		{
			Hannah.status = RunPosture;
			Hannah.HorizontalDirection = left;
			Hannah.VerticalDirection = none;
			StillBeginTime = 0;
		}

		//汉娜向右跑步
		if ((GetAsyncKeyState('D') & 0x8000) && ((GetAsyncKeyState(VK_SHIFT) & 0x8000)))
		{
			Hannah.status = RunPosture;
			Hannah.HorizontalDirection = right;
			Hannah.VerticalDirection = none;
			StillBeginTime = 0;
		}

		//汉娜向打空气
		if (GetAsyncKeyState('J'))
		{
			Hannah.status = AttackPosture;
			StillBeginTime = 0;
		}
	}

}

void HannahPostureAnimationShow()
{
	if (GameStatus == FirstStage || GameStatus==SecondStage || GameStatus==SecondStageFirstCutscene || GameStatus == ThirdStage)
	{
		//防卫
		if (Hannah.status == DefensivePosture)
		{
			if (Hannah.HorizontalDirection == left)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahDefensiveImgLeft);

			else if (Hannah.HorizontalDirection == right)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahDefensiveImgRight);
		}
		//静止
		else if (Hannah.status == StillPosture)
		{
			static int StillPostureCnt = 0;
			static DWORD StillPostureBeginTime = 0;
			DWORD StillPostureElapsedTime = 200;
			if (Hannah.HorizontalDirection == left)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahStillImgLeft[StillPostureCnt]);
			else if (Hannah.HorizontalDirection == right)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahStillImgRight[StillPostureCnt]);
			if (!StillPostureBeginTime)
				StillPostureBeginTime = GetTickCount();
			if (GetTickCount() - StillPostureBeginTime >= StillPostureElapsedTime)
			{
				StillPostureCnt++;
				if (StillPostureCnt > 3)
				{
					Hannah.status = DefensivePosture;
					StillPostureCnt = 0;
				}
				StillPostureBeginTime = 0;
				StillBeginTime = 0;
			}
		}

		//走路
		else if (Hannah.status == WalkPosture)
		{
			static int WalkPostureCnt = 0;
			static DWORD WalkPostureBeginTime = 0;
			static DWORD WalkPostureElapsedTime = 100;

			if (Hannah.VerticalDirection == up)
			{
				if (Hannah.HorizontalDirection == left)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgLeft[WalkPostureCnt]);
				else if (Hannah.HorizontalDirection == right)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgRight[WalkPostureCnt]);

				if (!WalkPostureBeginTime)
					WalkPostureBeginTime = GetTickCount();
				if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
				{
					WalkPostureCnt++;
					if (GameStatus == FirstStage)
					{
						if (Hannah.px >= 0 && Hannah.px <= 250)
						{
							if (Hannah.py >= Hannah.px / 0.52)
								Hannah.py -= Hannah.vy;
						}
						else
							Hannah.py -= Hannah.vy;
						if (Hannah.py <= 320)
							Hannah.py = 320;
					}

					else if (GameStatus == SecondStage)
					{
						Hannah.py -= Hannah.vy;
						if (Hannah.py <= 320)
							Hannah.py = 320;
					}

					else if (GameStatus == ThirdStage)
					{
						Hannah.py -= Hannah.vy;
						if (Hannah.py <= 320)
							Hannah.py = 320;
					}

					if ((WalkPostureCnt > 11) || (!(GetAsyncKeyState('W') & 0x8000)))
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
						Hannah.status = DefensivePosture;
					}

					WalkPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}

			if (Hannah.VerticalDirection == down)
			{
				if (Hannah.HorizontalDirection == left)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgLeft[WalkPostureCnt]);
				else if (Hannah.HorizontalDirection == right)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgRight[WalkPostureCnt]);

				if (!WalkPostureBeginTime)
					WalkPostureBeginTime = GetTickCount();
				if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
				{
					WalkPostureCnt++;
					if (GameStatus == FirstStage)
					{
						if (Hannah.px >= 0 && Hannah.px <= 250)
						{
							if (Hannah.py <= Hannah.px / 0.52)
								Hannah.py += Hannah.vy;
						}
						else
							Hannah.py += Hannah.vy;
						if (Hannah.py >= 450)
							Hannah.py = 450;
					}

					else if (GameStatus == SecondStage)
					{
						Hannah.py += Hannah.vy;
						if (Hannah.py >= 500)
							Hannah.py = 500;
					}

					else if (GameStatus == ThirdStage)
					{
						Hannah.py += Hannah.vy;
						if (Hannah.py >= 500)
							Hannah.py = 500;
					}

					if ((WalkPostureCnt > 11) || (!(GetAsyncKeyState('S') & 0x8000)))
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
						Hannah.status = DefensivePosture;
					}

					WalkPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}

			if (Hannah.HorizontalDirection == left && Hannah.VerticalDirection == none)
			{
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgLeft[WalkPostureCnt]);
				if (!WalkPostureBeginTime)
					WalkPostureBeginTime = GetTickCount();

				if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
				{
					WalkPostureCnt++;
					if (GameStatus == FirstStage)
					{
						double px = (Hannah.py - 320) / 0.52;
						if (px <= 40)
							px = 40;
						if (Hannah.px >= px)
							Hannah.px -= Hannah.vx;
						if (Hannah.px <= px)
							Hannah.px = px;
					}

					else if (GameStatus == SecondStage)
					{
						Hannah.px -= Hannah.vx;
						if (Hannah.px <= 150)
							Hannah.px = 150;
					}

					else if (GameStatus == ThirdStage)
					{
						Hannah.px -= Hannah.vx;
						if (Hannah.px <= 50)
							Hannah.px = 50;
					}


					if ((WalkPostureCnt > 11) || (!(GetAsyncKeyState('A') & 0x8000)))
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
						Hannah.status = DefensivePosture;
					}
					WalkPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}

			if (Hannah.HorizontalDirection == right && Hannah.VerticalDirection == none)
			{
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahWalkImgRight[WalkPostureCnt]);
				if (!WalkPostureBeginTime)
					WalkPostureBeginTime = GetTickCount();

				if (GetTickCount() - WalkPostureBeginTime >= WalkPostureElapsedTime)
				{
					WalkPostureCnt++;
					if (Hannah.px <= 1100)
						Hannah.px += Hannah.vx;

					if ((WalkPostureCnt > 11) || (!(GetAsyncKeyState('D') & 0x8000)))
					{
						WalkPostureCnt = 0;
						WalkPostureBeginTime = 0;
						Hannah.status = DefensivePosture;
					}
					WalkPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}
		}

		//跑步
		else if (Hannah.status == RunPosture)
		{
			static int RunPostureCnt = 0;
			static DWORD RunPostureBeginTime = 0;
			static DWORD RunPostureElapsedTime = 100;

			if (Hannah.VerticalDirection == up)
			{
				if (Hannah.HorizontalDirection == left)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahRunImgLeft[RunPostureCnt]);
				else if (Hannah.HorizontalDirection == right)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahRunImgRight[RunPostureCnt]);

				if (!RunPostureBeginTime)
					RunPostureBeginTime = GetTickCount();
				if (GetTickCount() - RunPostureBeginTime >= RunPostureElapsedTime)
				{
					RunPostureCnt++;
					if (GameStatus == FirstStage)
					{
						if (Hannah.px >= 0 && Hannah.px <= 250)
						{
							if (Hannah.py >= Hannah.px / 0.52)
								Hannah.py -= Hannah.vy;
						}
						else
							Hannah.py -= Hannah.vy;
						if (Hannah.py <= 320)
							Hannah.py = 320;
					}

					else if (GameStatus == SecondStage)
					{
						Hannah.py -= Hannah.vy;
						if (Hannah.py <= 320)
							Hannah.py = 320;
					}

					else if (GameStatus == ThirdStage)
					{
						Hannah.py -= Hannah.vy;
						if (Hannah.py <= 320)
							Hannah.py = 320;
					}

					if ((RunPostureCnt > 8) || (!(GetAsyncKeyState('W') & 0x8000)) || (!(GetAsyncKeyState(VK_SHIFT) & 0x8000)))
					{
						RunPostureCnt = 0;
						RunPostureBeginTime = 0;
						Hannah.status = DefensivePosture;
					}

					RunPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}

			if (Hannah.VerticalDirection == down)
			{
				if (Hannah.HorizontalDirection == left)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahRunImgLeft[RunPostureCnt]);
				else if (Hannah.HorizontalDirection == right)
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahRunImgRight[RunPostureCnt]);

				if (!RunPostureBeginTime)
					RunPostureBeginTime = GetTickCount();
				if (GetTickCount() - RunPostureBeginTime >= RunPostureElapsedTime)
				{
					RunPostureCnt++;
					if (GameStatus == FirstStage)
					{
						if (Hannah.px >= 0 && Hannah.px <= 250)
						{
							if (Hannah.py <= Hannah.px / 0.52)
								Hannah.py += Hannah.vy;
						}
						else
							Hannah.py += Hannah.vy;
						if (Hannah.py >= 450)
							Hannah.py = 450;
					}

					else if (GameStatus == SecondStage)
					{
						Hannah.py += Hannah.vy;
						if (Hannah.py >= 500)
							Hannah.py = 500;
					}

					else if (GameStatus == ThirdStage)
					{
						Hannah.py += Hannah.vy;
						if (Hannah.py >= 500)
							Hannah.py = 500;
					}

						if ((RunPostureCnt > 8) || (!(GetAsyncKeyState('S') & 0x8000)) || (!(GetAsyncKeyState(VK_SHIFT) & 0x8000)))
						{
							RunPostureCnt = 0;
							RunPostureBeginTime = 0;
							Hannah.status = DefensivePosture;
						}
					RunPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}

			if (Hannah.HorizontalDirection == left && Hannah.VerticalDirection == none)
			{
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahRunImgLeft[RunPostureCnt]);
				if (!RunPostureBeginTime)
					RunPostureBeginTime = GetTickCount();

				if (GetTickCount() - RunPostureBeginTime >= RunPostureElapsedTime)
				{
					RunPostureCnt++;
					if (GameStatus == FirstStage)
					{
						double px = (Hannah.py - 320) / 0.52;
						if (px <= 40)
							px = 40;
						if (Hannah.px >= px)
							Hannah.px -= Hannah.vx*2;
						if (Hannah.px <= px)
							Hannah.px = px;
					}

					else if (GameStatus == SecondStage)
					{
						Hannah.px -= Hannah.vx*2;
						if (Hannah.px <= 150)
							Hannah.px = 150;
					}

					else if (GameStatus == ThirdStage)
					{
						Hannah.px -= Hannah.vx * 2;
						if (Hannah.px <= 50)
							Hannah.px = 50;
					}

					if ((RunPostureCnt > 8) || (!(GetAsyncKeyState('A') & 0x8000)) || (!(GetAsyncKeyState(VK_SHIFT) & 0x8000)))
					{
						RunPostureCnt = 0;
						RunPostureBeginTime = 0;
						Hannah.status = DefensivePosture;
					}
					RunPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}

			if (Hannah.HorizontalDirection == right && Hannah.VerticalDirection == none)
			{
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahRunImgRight[RunPostureCnt]);
				if (!RunPostureBeginTime)
					RunPostureBeginTime = GetTickCount();

				if (GetTickCount() - RunPostureBeginTime >= RunPostureElapsedTime)
				{
					RunPostureCnt++;
					if (Hannah.px <= 1100)
						Hannah.px += Hannah.vx;

					if ((RunPostureCnt > 8) || (!(GetAsyncKeyState('D') & 0x8000)) || (!(GetAsyncKeyState(VK_SHIFT) & 0x8000)))
					{
						RunPostureCnt = 0;
						RunPostureBeginTime = 0;
						Hannah.status = DefensivePosture;
					}
					RunPostureBeginTime = 0;
					StillBeginTime = 0;
				}
			}
		}

		//汉娜攻击
		else if (Hannah.status == AttackPosture)
		{
			static DWORD AttackPostureFirstBeginTime = 0;
			DWORD AttackPostureFirstElapsedTime = 250;

			if (Hannah.HorizontalDirection == left)
			{
				if (HannahAttackPostureFirstCnt == 1)
					transparentimage(NULL, Hannah.px - 90, Hannah.py, &HannahAttackImgLeft[HannahAttackPostureFirstCnt]);
				else
					transparentimage(NULL, Hannah.px, Hannah.py, &HannahAttackImgLeft[HannahAttackPostureFirstCnt]);
				if (!AttackPostureFirstBeginTime)
					AttackPostureFirstBeginTime = GetTickCount();
				if (GetTickCount() - AttackPostureFirstBeginTime >= AttackPostureFirstElapsedTime)
				{
					HannahAttackPostureFirstCnt++;
					{
						if ((HannahAttackPostureFirstCnt > 1))
						{
							HannahAttackPostureFirstCnt = 0;
							AttackPostureFirstBeginTime = 0;
							Hannah.status = DefensivePosture;
						}
					}
					AttackPostureFirstBeginTime = 0;
					StillBeginTime = 0;
				}
			}

			if (Hannah.HorizontalDirection == right)
			{
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahAttackImgRight[HannahAttackPostureFirstCnt]);
				if (!AttackPostureFirstBeginTime)
					AttackPostureFirstBeginTime = GetTickCount();
				if (GetTickCount() - AttackPostureFirstBeginTime >= AttackPostureFirstElapsedTime)
				{
					HannahAttackPostureFirstCnt++;
					{
						if ((HannahAttackPostureFirstCnt > 1))
						{
							HannahAttackPostureFirstCnt = 0;
							AttackPostureFirstBeginTime = 0;
							Hannah.status = DefensivePosture;
						}
					}
					AttackPostureFirstBeginTime = 0;
					StillBeginTime = 0;
				}
			}
		}


		//被击倒
		else if (Hannah.status == WasKonckedDown)
		{

			if (Hannah.WasAttackDirection==left)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahWasKnockedDownImgLeft[0]);
			else if (Hannah.WasAttackDirection == right)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahWasKnockedDownImgRight[0]);

			if (Hannah.status != AttackPosture)
				Hannah.status = DefensivePosture;
		}

		else if (Hannah.status == DeathPosture)
		{
			static int direction = 0;
			direction = Hannah.HorizontalDirection;

			static int DeathAnimationCnt = 0;
			static DWORD DeathAnimationBeginTime = 0;
			DWORD DeathAnimationElapsedTime = 250;

			static double px = Hannah.px;
			static double py = Hannah.py;

			if (!DeathAnimationCnt)
			{
				px = Hannah.px;
				py = Hannah.py;
			}

			if (!DeathAnimationBeginTime)
				DeathAnimationBeginTime = GetTickCount();


			if (Hannah.WasAttackDirection == left)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahWasKnockedDownImgLeft[DeathAnimationCnt]);
			else if (Hannah.WasAttackDirection == right)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahWasKnockedDownImgRight[DeathAnimationCnt]);

			if (GetTickCount() - DeathAnimationBeginTime >= DeathAnimationElapsedTime)
			{
				DeathAnimationCnt++;
				if (DeathAnimationCnt == 1)
				{
					Hannah.px = px - 10;
					Hannah.py = py + 25;
				}

				else if (DeathAnimationCnt == 2)
				{
					Hannah.px = px - 20;
					Hannah.py = py + 60;
				}
				else if (DeathAnimationCnt == 3)
				{
					Hannah.px = px - 30;
					Hannah.py = py + 60;
				}
				else if (DeathAnimationCnt == 4)
				{
					Hannah.px = px - 40;
					Hannah.py = py + 60;
				}
				else if (DeathAnimationCnt == 5)
				{
					Hannah.px = px - 50;
					Hannah.py = py + 145;
				}
				if (DeathAnimationCnt > 5)
				{
					DeathAnimationCnt = 0;
					Hannah.py = 2000;
				}
				DeathAnimationBeginTime = 0;
			}
		}

		else if (Hannah.status == VictoryPosture)
		{
			static int VictoryPostureCnt = 0;
			static DWORD VictoryPostureBeginTime = 0;
			DWORD VictoryPostureElapsedTime = 250;

			if (!VictoryPostureBeginTime)
				VictoryPostureBeginTime = GetTickCount();
			if (Hannah.HorizontalDirection == left)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahVictoryImgLeft[VictoryPostureCnt]);
			else if (Hannah.HorizontalDirection == right)
				transparentimage(NULL, Hannah.px, Hannah.py, &HannahVictoryImgRight[VictoryPostureCnt]);
			transparentimage(NULL, Hannah.px - 42, Hannah.py - 52, &HannahVictoryImgRight[4]);
			if (GetTickCount() - VictoryPostureBeginTime >= VictoryPostureElapsedTime)
			{
				VictoryPostureCnt++;
				if (VictoryPostureCnt > 3)
				{
					VictoryPostureCnt = 0;
				}
				VictoryPostureBeginTime = 0;
				StillBeginTime = 0;
			}
		}
	}
}

//小怪A
static DWORD EnemyAStillBeginTime = 0;
void EnemyAStatusChange()
{
	if (GameStatus == FirstStage || GameStatus==SecondStage &&!EnemyA.IsSpecialPosture)
	{
		if (Hannah.px - EnemyA.px >= 0)
			EnemyA.HorizontalDirection = right;
		else if (Hannah.px - EnemyA.px <= 0)
			EnemyA.HorizontalDirection = left;

		DWORD EnemyAElapsedTime = 1000;

		if (!EnemyA.BeginTime)
			EnemyA.BeginTime = GetTickCount();

		if (sqrt((Hannah.px - EnemyA.px) * (Hannah.px - EnemyA.px) - (Hannah.py - EnemyA.py) * (Hannah.py - EnemyA.py)) >= 300)
		{
			if (!EnemyAStillBeginTime)
				EnemyAStillBeginTime = GetTickCount();

			if (GetTickCount() - EnemyAStillBeginTime >= EnemyAElapsedTime)
				EnemyA.status = StillPosture;
		}

		else if(sqrt((Hannah.px - EnemyA.px) * (Hannah.px - EnemyA.px) - (Hannah.py - EnemyA.py) * (Hannah.py - EnemyA.py)) <= 300)
		{
			EnemyAStillBeginTime = 0;
			if (EnemyA.HorizontalDirection == left&&EnemyA.status!=WasKonckedDown)
			{
				if (EnemyA.px - 90 <= Hannah.px + 80 && EnemyA.px + 92 - 90 >= Hannah.px && EnemyA.py + 10 <= Hannah.py + 151 && EnemyA.py + 10 + 19 >= Hannah.py)
					EnemyA.status = AttackPosture;
				else
					EnemyA.status = TrackPosture;
			}
			else if (EnemyA.HorizontalDirection == right && EnemyA.status != WasKonckedDown)
			{
				if (EnemyA.px + 130 <= Hannah.px + 91 && EnemyA.px + 130 + 87 >= Hannah.px && EnemyA.py + 10 <= Hannah.py + 154 && EnemyA.py + 10 + 21 >= Hannah.py)
					EnemyA.status = AttackPosture;
				else
					EnemyA.status = TrackPosture;
			}
			else
				EnemyA.status = TrackPosture;
			EnemyA.BeginTime = 0;
		}

		static DWORD IsShouldRestBeginTime = 0;
		DWORD IsShouldRestElapsedTime = 2000;

		if (EnemyA.IsShouldRest)
		{
			EnemyA.status = DefensivePosture;
			IsShouldRestBeginTime = GetTickCount();
		}

		else if (GetTickCount() - IsShouldRestBeginTime >= IsShouldRestElapsedTime&&EnemyA.IsShouldRest)
		{
			EnemyA.IsShouldRest = false;
		}

		if (EnemyA.life <= 0)
			EnemyA.status = DeathPosture;
	}

}

static int EnemyAAttackPosturetCnt = 0;
void EnemyAPostureAnimationShow()
{
	if ((GameStatus == FirstStage || GameStatus == SecondStage) && !EnemyA.IsSpecialPosture)
	{
		//防卫
		if (EnemyA.status == DefensivePosture)
		{
			if (EnemyA.HorizontalDirection == left)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyADefensiveImgLeft);

			else if (EnemyA.HorizontalDirection == right)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyADefensiveImgRight);
		}

		//静止
		else if (EnemyA.status == StillPosture)
		{
			static int StillPostureCnt = 0;
			static DWORD StillPostureBeginTime = 0;
			DWORD StillPostureElapsedTime = 250;
			if (EnemyA.HorizontalDirection == left)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAStillImgLeft[StillPostureCnt]);
			else if (EnemyA.HorizontalDirection == right)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAStillImgRight[StillPostureCnt]);
			if (!StillPostureBeginTime)
				StillPostureBeginTime = GetTickCount();
			if (GetTickCount() - StillPostureBeginTime >= StillPostureElapsedTime)
			{
				StillPostureCnt++;
				if (StillPostureCnt > 2)
				{
					EnemyA.status = RandWalk;
					StillPostureCnt = 0;
				}
				StillPostureBeginTime = 0;
				EnemyAStillBeginTime = 0;
			}
		}

		//随机走路
		else if (EnemyA.status == RandWalk)
		{
			static int RandWalkCnt = 0;
			static DWORD RandWalkBeginTime = 0;
			DWORD RandWalkElapsedTime = 100;

			if (!EnemyA.BeginTime)
				EnemyA.BeginTime = GetTickCount();

			if (Hannah.px - EnemyA.px <= 0)
				EnemyA.HorizontalDirection = left;

			else if (Hannah.px - EnemyA.px >= 0)
				EnemyA.HorizontalDirection = right;

			if (EnemyA.HorizontalDirection == left)
			{
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWalkImgLeft[RandWalkCnt]);
				if (!RandWalkBeginTime)
					RandWalkBeginTime = GetTickCount();
				if (GetTickCount() - RandWalkBeginTime >= RandWalkElapsedTime)
				{
					if (RandWalkCnt == 0)
						EnemyA.py -= EnemyA.vy;//上
					else if (RandWalkCnt == 1)
						EnemyA.px -= EnemyA.vx;//左
					else if (RandWalkCnt == 2)
						EnemyA.px -= EnemyA.vx;//左
					else if (RandWalkCnt == 3)
						EnemyA.py += EnemyA.vy;//下
					else if (RandWalkCnt == 4)
						EnemyA.px += EnemyA.vx;//右
					else if (RandWalkCnt == 5)
						EnemyA.px += EnemyA.vx;//右
					RandWalkCnt++;
					if (RandWalkCnt > 5)
					{
						RandWalkCnt = 0;
						if (GetTickCount() - EnemyA.BeginTime >= EnemyA.ElapsedTime * 2)
						{
							EnemyA.status = StillPosture;
							EnemyA.BeginTime = 0;
						}
					}
					EnemyAStillBeginTime = 0;
					RandWalkBeginTime = 0;
				}
			}

			if (EnemyA.HorizontalDirection == right)
			{
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWalkImgRight[RandWalkCnt]);
				if (!RandWalkBeginTime)
					RandWalkBeginTime = GetTickCount();
				if (GetTickCount() - RandWalkBeginTime >= RandWalkElapsedTime)
				{
					if (RandWalkCnt == 0)
						EnemyA.py -= EnemyA.vy;//上
					else if (RandWalkCnt == 1)
						EnemyA.px -= EnemyA.vx;//左
					else if (RandWalkCnt == 2)
						EnemyA.px -= EnemyA.vx;//左
					else if (RandWalkCnt == 3)
						EnemyA.py += EnemyA.vy;//下
					else if (RandWalkCnt == 4)
						EnemyA.px += EnemyA.vx;//右
					else if (RandWalkCnt == 5)
						EnemyA.px += EnemyA.vx;//右
					RandWalkCnt++;
					if (RandWalkCnt > 5)
					{
						RandWalkCnt = 0;
						if (GetTickCount() - EnemyA.BeginTime >= EnemyA.ElapsedTime * 2)
						{
							EnemyA.status = StillPosture;
							EnemyA.BeginTime = 0;
						}
					}
					RandWalkBeginTime = 0;
				}
			}
		}

		//追踪主角
		else if (EnemyA.status == TrackPosture)
		{
			static int TrackHannahCnt = 0;
			static DWORD TrackHannahBeginTime = 0;
			DWORD TrackHannahElapsedTime = 140;

			if (!EnemyA.BeginTime)
				EnemyA.BeginTime = GetTickCount();

			if (EnemyA.HorizontalDirection == left)
			{
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWalkImgLeft[TrackHannahCnt]);
				if (!TrackHannahBeginTime)
					TrackHannahBeginTime = GetTickCount();
				if (GetTickCount() - TrackHannahBeginTime >= TrackHannahElapsedTime)
				{
					TrackHannahCnt++;
					if (fabs(Hannah.px - EnemyA.px) >= 150 && Hannah.HorizontalDirection == left)
						EnemyA.px -= (Hannah.px - EnemyA.px) / 50;
					else if (fabs(Hannah.px - EnemyA.px) >= 150 && Hannah.HorizontalDirection == right)
						EnemyA.px += (Hannah.px - EnemyA.px) / 50;
					EnemyA.py += (Hannah.py - EnemyA.py - 10) / 150;
					if (TrackHannahCnt > 6)
					{
						TrackHannahCnt = 0;
						if (GetTickCount() - EnemyA.BeginTime >= EnemyA.ElapsedTime * 10)
						{
							EnemyA.IsShouldRest = true;
							EnemyA.BeginTime = 0;
						}
					}
					TrackHannahBeginTime = 0;
				}
			}

			else if (EnemyA.HorizontalDirection == right)
			{
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWalkImgRight[TrackHannahCnt]);
				if (!TrackHannahBeginTime)
					TrackHannahBeginTime = GetTickCount();
				if (GetTickCount() - TrackHannahBeginTime >= TrackHannahElapsedTime)
				{
					TrackHannahCnt++;
					if (fabs(Hannah.px - EnemyA.px) >= 150)
						EnemyA.px += (Hannah.px - EnemyA.px) / 50;
					EnemyA.py += (Hannah.py - EnemyA.py - 10) / 150;
					if (TrackHannahCnt > 6)
					{
						TrackHannahCnt = 0;
						if (GetTickCount() - EnemyA.BeginTime >= EnemyA.ElapsedTime * 10)
						{
							EnemyA.IsShouldRest = true;
							EnemyA.BeginTime = 0;
						}
					}
					TrackHannahBeginTime = 0;
				}
			}
		}


		//小怪攻击
		else if (EnemyA.status == AttackPosture)
		{
			static DWORD AttackPosturetBeginTime = 0;
			DWORD AttackPostureElapsedTime = 500;

			if (EnemyA.HorizontalDirection == left)
			{
				if (EnemyAAttackPosturetCnt == 2)
					transparentimage(NULL, EnemyA.px - 90, EnemyA.py, &EnemyAAttackImgLeft[2]);
				else
					transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAAttackImgLeft[EnemyAAttackPosturetCnt]);
				if (!AttackPosturetBeginTime)
					AttackPosturetBeginTime = GetTickCount();
				if (GetTickCount() - AttackPosturetBeginTime >= AttackPostureElapsedTime)
				{
					EnemyAAttackPosturetCnt++;
					{
						if ((EnemyAAttackPosturetCnt > 2))
						{
							EnemyAAttackPosturetCnt = 0;
							AttackPosturetBeginTime = 0;
							EnemyA.status = RandWalk;
						}
					}
					AttackPosturetBeginTime = 0;
					EnemyAStillBeginTime = 0;
				}
			}

			if (EnemyA.HorizontalDirection == right)
			{
				if (EnemyAAttackPosturetCnt == 2)
					transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAAttackImgRight[2]);
				else
					transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAAttackImgRight[EnemyAAttackPosturetCnt]);
				if (!AttackPosturetBeginTime)
					AttackPosturetBeginTime = GetTickCount();
				if (GetTickCount() - AttackPosturetBeginTime >= AttackPostureElapsedTime)
				{
					EnemyAAttackPosturetCnt++;
					{
						if ((EnemyAAttackPosturetCnt > 2))
						{
							EnemyAAttackPosturetCnt = 0;
							AttackPosturetBeginTime = 0;
							EnemyA.status = RandWalk;
						}
					}
					AttackPosturetBeginTime = 0;
					EnemyAStillBeginTime = 0;
				}
			}
		}


		//被击倒
		else if (EnemyA.status == WasKonckedDown)
		{

			if (EnemyA.WasAttackDirection == left)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWasKnockedDownImgLeft[0]);
			else if (EnemyA.WasAttackDirection == right)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWasKnockedDownImgRight[0]);

			if (EnemyA.status != AttackPosture)
				EnemyA.status = DefensivePosture;
		}

		else if (EnemyA.status == DeathPosture)
		{

			static int DeathAnimationCnt = 0;
			static DWORD DeathAnimationBeginTime = 0;
			DWORD DeathAnimationElapsedTime = 250;

			static double px = EnemyA.px;
			static double py = EnemyA.py;

			if (!DeathAnimationCnt)
			{
				px = EnemyA.px;
				py = EnemyA.py;
			}

			if (!DeathAnimationBeginTime)
				DeathAnimationBeginTime = GetTickCount();


			if (EnemyA.WasAttackDirection == left)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWasKnockedDownImgLeft[DeathAnimationCnt]);
			else if (EnemyA.WasAttackDirection == right)
				transparentimage(NULL, EnemyA.px, EnemyA.py, &EnemyAWasKnockedDownImgRight[DeathAnimationCnt]);

			if (GetTickCount() - DeathAnimationBeginTime >= DeathAnimationElapsedTime)
			{
				DeathAnimationCnt++;
				if (DeathAnimationCnt == 1)
				{
					EnemyA.px = px - 10;
					EnemyA.py = py + 65;
				}

				else if (DeathAnimationCnt == 2)
				{
					EnemyA.px = px - 20;
					EnemyA.py = py + 40;
				}
				else if (DeathAnimationCnt == 3)
				{
					EnemyA.px = px - 30;
					EnemyA.py = py + 100;
				}
				else if (DeathAnimationCnt == 4)
				{
					EnemyA.px = px - 40;
					EnemyA.py = py + 130;
				}

				if (DeathAnimationCnt > 4)
				{
					DeathAnimationCnt = 0;
					EnemyA.flag = FirstStageEnd;
					EnemyA.py = 2000;
				}
				DeathAnimationBeginTime = 0;
			}
		}
	}
}

void EnemyAWasAttackByHannahCheck()
{
	if (GameStatus == FirstStage || GameStatus==SecondStage)
	{
		if (Hannah.status == AttackPosture && HannahAttackPostureFirstCnt == 1)
		{
			if (Hannah.HorizontalDirection == left)
			{
				if (EnemyA.px <= Hannah.px - 90 + 92 && EnemyA.px + 87 >= Hannah.px - 90 && EnemyA.py <= Hannah.py + 10 + 23 && EnemyA.py + 127 >= Hannah.py + 10)
				{
					EnemyA.status = WasKonckedDown;
					EnemyA.WasAttackDirection = right;
					if (EnemyA.life >= 5)
						EnemyA.life -= 5;
					if (EnemyA.life <= 0 && EnemyA.status != DeathPosture)
					{
						EnemyA.status = DeathPosture;
						int x = rand() % 4;
						Food.status = x;
						Food.px = EnemyA.px;
						Food.py = EnemyA.py + 150;
					}
				}
			}

			else if (Hannah.HorizontalDirection == right)
			{
				if (EnemyA.px <= Hannah.px + 76 + 100 && EnemyA.px + 96 >= Hannah.px + 76 && EnemyA.py <= Hannah.py + 10 + 14 && EnemyA.py + 145 >= Hannah.py + 10)
				{
					EnemyA.status = WasKonckedDown;
					EnemyA.WasAttackDirection = left;
					if (EnemyA.life >= 5)
						EnemyA.life -= 5;
					if (EnemyA.life <= 0 && EnemyA.status != DeathPosture)
					{
						EnemyA.status = DeathPosture;
						int x = rand() % 4;
						Food.status = x;
						Food.px = EnemyA.px;
						Food.py = EnemyA.py + 150;
					}
				}
			}
		}
	}
}

void HannahWasAttackByEnemyACheck()
{
	if (GameStatus == FirstStage || GameStatus==SecondStage)
	{
		if (EnemyA.status == AttackPosture && EnemyAAttackPosturetCnt == 2)
		{
			if (EnemyA.HorizontalDirection == left)
			{
				if (EnemyA.px - 90 <= Hannah.px + 80 && EnemyA.px + 92 - 90 >= Hannah.px && EnemyA.py + 10 <= Hannah.py + 151 && EnemyA.py + 10 + 19 >= Hannah.py)
				{
					Hannah.status = WasKonckedDown;
					Hannah.WasAttackDirection = right;
					StillBeginTime = 0;
					if (Hannah.life >= 3)
						Hannah.life -= 3;
					if (Hannah.life <= 0)
						Hannah.status = DeathPosture;
				}
			}

			else if (EnemyA.HorizontalDirection == right)
			{
				if (EnemyA.px + 130 <= Hannah.px + 91 && EnemyA.px + 130 + 87 >= Hannah.px && EnemyA.py + 10 <= Hannah.py + 154 && EnemyA.py + 10 + 21 >= Hannah.py)
				{
					Hannah.status = WasKonckedDown;
					Hannah.WasAttackDirection = left;
					StillBeginTime = 0;
					if (Hannah.life >= 3)
						Hannah.life -= 3;
					if (Hannah.life <= 0)
						Hannah.status = DeathPosture;
				}
			}
		}
	}
}

//小怪B
static DWORD EnemyBStillBeginTime = 0;
void EnemyBStatusChange()
{
	if (GameStatus == FirstStage || GameStatus == SecondStage)
	{
		if (Hannah.px - EnemyB.px >= 0)
			EnemyB.HorizontalDirection = right;
		else if (Hannah.px - EnemyB.px <= 0)
			EnemyB.HorizontalDirection = left;

		DWORD EnemyBElapsedTime = 1000;

		if (!EnemyB.BeginTime)
			EnemyB.BeginTime = GetTickCount();

		if (sqrt((Hannah.px - EnemyB.px) * (Hannah.px - EnemyB.px) - (Hannah.py - EnemyB.py) * (Hannah.py - EnemyB.py)) >= 300)
		{
			if (!EnemyBStillBeginTime)
				EnemyBStillBeginTime = GetTickCount();

			if (GetTickCount() - EnemyBStillBeginTime >= EnemyBElapsedTime)
				EnemyB.status = StillPosture;
		}

		else if (sqrt((Hannah.px - EnemyB.px) * (Hannah.px - EnemyB.px) - (Hannah.py - EnemyB.py) * (Hannah.py - EnemyB.py)) <= 300)
		{
			EnemyBStillBeginTime = 0;
			if (EnemyB.HorizontalDirection == left && EnemyB.status != WasKonckedDown)
			{
				if (EnemyB.px - 90 <= Hannah.px + 80 && EnemyB.px + 92 - 90 >= Hannah.px && EnemyB.py + 10 <= Hannah.py + 151 && EnemyB.py + 10 + 19 >= Hannah.py)
					EnemyB.status = AttackPosture;
				else
					EnemyB.status = TrackPosture;
			}
			else if (EnemyB.HorizontalDirection == right && EnemyB.status != WasKonckedDown)
			{
				if (EnemyB.px + 130 <= Hannah.px + 91 && EnemyB.px + 130 + 87 >= Hannah.px && EnemyB.py + 10 <= Hannah.py + 154 && EnemyB.py + 10 + 21 >= Hannah.py)
					EnemyB.status = AttackPosture;
				else
					EnemyB.status = TrackPosture;
			}
			else
				EnemyB.status = TrackPosture;
			EnemyB.BeginTime = 0;
		}

		static DWORD IsShouldRestBeginTime = 0;
		DWORD IsShouldRestElapsedTime = 2000;

		if (EnemyB.IsShouldRest)
		{
			EnemyB.status = DefensivePosture;
			IsShouldRestBeginTime = GetTickCount();
		}

		else if (GetTickCount() - IsShouldRestBeginTime >= IsShouldRestElapsedTime && EnemyB.IsShouldRest)
		{
			EnemyB.IsShouldRest = false;
		}

		if (EnemyB.life <= 0)
			EnemyB.status = DeathPosture;
	}
}

static int EnemyBAttackPosturetCnt = 0;
void EnemyBPostureAnimationShow()
{
	if (GameStatus == FirstStage || GameStatus==SecondStage)
	{
		//防卫
		if (EnemyB.status == DefensivePosture)
		{
			if (EnemyB.HorizontalDirection == left)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBDefensiveImgLeft);

			else if (EnemyB.HorizontalDirection == right)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBDefensiveImgRight);
		}

		//静止
		else if (EnemyB.status == StillPosture)
		{
			static int StillPostureCnt = 0;
			static DWORD StillPostureBeginTime = 0;
			DWORD StillPostureElapsedTime = 250;
			if (EnemyB.HorizontalDirection == left)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBStillImgLeft[StillPostureCnt]);
			else if (EnemyB.HorizontalDirection == right)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBStillImgRight[StillPostureCnt]);
			if (!StillPostureBeginTime)
				StillPostureBeginTime = GetTickCount();
			if (GetTickCount() - StillPostureBeginTime >= StillPostureElapsedTime)
			{
				StillPostureCnt++;
				if (StillPostureCnt > 2)
				{
					EnemyB.status = RandWalk;
					StillPostureCnt = 0;
				}
				StillPostureBeginTime = 0;
				EnemyBStillBeginTime = 0;
			}
		}

		//随机走路
		else if (EnemyB.status == RandWalk)
		{
			static int RandWalkCnt = 0;
			static DWORD RandWalkBeginTime = 0;
			DWORD RandWalkElapsedTime = 100;

			if (!EnemyB.BeginTime)
				EnemyB.BeginTime = GetTickCount();

			if (Hannah.px - EnemyB.px <= 0)
				EnemyB.HorizontalDirection = left;

			else if (Hannah.px - EnemyB.px >= 0)
				EnemyB.HorizontalDirection = right;

			if (EnemyB.HorizontalDirection == left)
			{
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWalkImgLeft[RandWalkCnt]);
				if (!RandWalkBeginTime)
					RandWalkBeginTime = GetTickCount();
				if (GetTickCount() - RandWalkBeginTime >= RandWalkElapsedTime)
				{
					if (RandWalkCnt == 0)
						EnemyB.py -= EnemyB.vy;//上
					else if (RandWalkCnt == 1)
						EnemyB.px -= EnemyB.vx;//左
					else if (RandWalkCnt == 2)
						EnemyB.px -= EnemyB.vx;//左
					else if (RandWalkCnt == 3)
						EnemyB.py += EnemyB.vy;//下
					else if (RandWalkCnt == 4)
						EnemyB.px += EnemyB.vx;//右
					else if (RandWalkCnt == 5)
						EnemyB.px += EnemyB.vx;//右
					RandWalkCnt++;
					if (RandWalkCnt > 5)
					{
						RandWalkCnt = 0;
						if (GetTickCount() - EnemyB.BeginTime >= EnemyB.ElapsedTime * 2)
						{
							EnemyB.status = StillPosture;
							EnemyB.BeginTime = 0;
						}
					}
					EnemyBStillBeginTime = 0;
					RandWalkBeginTime = 0;
				}
			}

			if (EnemyB.HorizontalDirection == right)
			{
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWalkImgRight[RandWalkCnt]);
				if (!RandWalkBeginTime)
					RandWalkBeginTime = GetTickCount();
				if (GetTickCount() - RandWalkBeginTime >= RandWalkElapsedTime)
				{
					if (RandWalkCnt == 0)
						EnemyB.py -= EnemyB.vy;//上
					else if (RandWalkCnt == 1)
						EnemyB.px -= EnemyB.vx;//左
					else if (RandWalkCnt == 2)
						EnemyB.px -= EnemyB.vx;//左
					else if (RandWalkCnt == 3)
						EnemyB.py += EnemyB.vy;//下
					else if (RandWalkCnt == 4)
						EnemyB.px += EnemyB.vx;//右
					else if (RandWalkCnt == 5)
						EnemyB.px += EnemyB.vx;//右
					RandWalkCnt++;
					if (RandWalkCnt > 5)
					{
						RandWalkCnt = 0;
						if (GetTickCount() - EnemyB.BeginTime >= EnemyB.ElapsedTime * 2)
						{
							EnemyB.status = StillPosture;
							EnemyB.BeginTime = 0;
						}
					}
					RandWalkBeginTime = 0;
				}
			}
		}

		//追踪主角
		else if (EnemyB.status == TrackPosture)
		{
			static int TrackHannahCnt = 0;
			static DWORD TrackHannahBeginTime = 0;
			DWORD TrackHannahElapsedTime = 140;

			if (!EnemyB.BeginTime)
				EnemyB.BeginTime = GetTickCount();

			if (EnemyB.HorizontalDirection == left)
			{
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWalkImgLeft[TrackHannahCnt]);
				if (!TrackHannahBeginTime)
					TrackHannahBeginTime = GetTickCount();
				if (GetTickCount() - TrackHannahBeginTime >= TrackHannahElapsedTime)
				{
					TrackHannahCnt++;
					if (fabs(Hannah.px - EnemyB.px) >= 150)
						EnemyB.px += (Hannah.px - EnemyB.px) / 50;
					EnemyB.py += (Hannah.py - EnemyB.py - 10) / 150;
					if (TrackHannahCnt > 6)
					{
						TrackHannahCnt = 0;
						if (GetTickCount() - EnemyB.BeginTime >= EnemyB.ElapsedTime * 10)
						{
							EnemyB.IsShouldRest = true;
							EnemyB.BeginTime = 0;
						}
					}
					TrackHannahBeginTime = 0;
				}
			}

			else if (EnemyB.HorizontalDirection == right)
			{
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWalkImgRight[TrackHannahCnt]);
				if (!TrackHannahBeginTime)
					TrackHannahBeginTime = GetTickCount();
				if (GetTickCount() - TrackHannahBeginTime >= TrackHannahElapsedTime)
				{
					TrackHannahCnt++;
					if (fabs(Hannah.px - EnemyB.px) >= 150)
						EnemyB.px += (Hannah.px - EnemyB.px) / 50;
					EnemyB.py += (Hannah.py - EnemyB.py - 10) / 150;
					if (TrackHannahCnt > 6)
					{
						TrackHannahCnt = 0;
						if (GetTickCount() - EnemyB.BeginTime >= EnemyB.ElapsedTime * 10)
						{
							EnemyB.IsShouldRest = true;
							EnemyB.BeginTime = 0;
						}
					}
					TrackHannahBeginTime = 0;
				}
			}
		}


		//小怪攻击
		else if (EnemyB.status == AttackPosture)
		{
			static DWORD AttackPosturetBeginTime = 0;
			DWORD AttackPostureElapsedTime = 500;

			if (EnemyB.HorizontalDirection == left)
			{
				if (EnemyBAttackPosturetCnt == 2)
					transparentimage(NULL, EnemyB.px - 90, EnemyB.py, &EnemyBAttackImgLeft[2]);
				else
					transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBAttackImgLeft[EnemyBAttackPosturetCnt]);
				if (!AttackPosturetBeginTime)
					AttackPosturetBeginTime = GetTickCount();
				if (GetTickCount() - AttackPosturetBeginTime >= AttackPostureElapsedTime)
				{
					EnemyBAttackPosturetCnt++;
					{
						if ((EnemyBAttackPosturetCnt > 2))
						{
							EnemyBAttackPosturetCnt = 0;
							AttackPosturetBeginTime = 0;
							EnemyB.status = RandWalk;
						}
					}
					AttackPosturetBeginTime = 0;
					EnemyBStillBeginTime = 0;
				}
			}

			if (EnemyB.HorizontalDirection == right)
			{
				if (EnemyBAttackPosturetCnt == 2)
					transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBAttackImgRight[2]);
				else
					transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBAttackImgRight[EnemyBAttackPosturetCnt]);
				if (!AttackPosturetBeginTime)
					AttackPosturetBeginTime = GetTickCount();
				if (GetTickCount() - AttackPosturetBeginTime >= AttackPostureElapsedTime)
				{
					EnemyBAttackPosturetCnt++;
					{
						if ((EnemyBAttackPosturetCnt > 2))
						{
							EnemyBAttackPosturetCnt = 0;
							AttackPosturetBeginTime = 0;
							EnemyB.status = RandWalk;
						}
					}
					AttackPosturetBeginTime = 0;
					EnemyBStillBeginTime = 0;
				}
			}
		}


		//被击倒
		else if (EnemyB.status == WasKonckedDown)
		{

			if (EnemyB.WasAttackDirection == left)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWasKnockedDownImgLeft[0]);
			else if (EnemyB.WasAttackDirection == right)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWasKnockedDownImgRight[0]);

			if (EnemyB.status != AttackPosture)
				EnemyB.status = DefensivePosture;
		}

		else if (EnemyB.status == DeathPosture)
		{

			static int DeathAnimationCnt = 0;
			static DWORD DeathAnimationBeginTime = 0;
			DWORD DeathAnimationElapsedTime = 250;

			static double px = EnemyB.px;
			static double py = EnemyB.py;

			if (!DeathAnimationCnt)
			{
				px = EnemyB.px;
				py = EnemyB.py;
			}

			if (!DeathAnimationBeginTime)
				DeathAnimationBeginTime = GetTickCount();


			if (EnemyB.WasAttackDirection == left)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWasKnockedDownImgLeft[DeathAnimationCnt]);
			else if (EnemyB.WasAttackDirection == right)
				transparentimage(NULL, EnemyB.px, EnemyB.py, &EnemyBWasKnockedDownImgRight[DeathAnimationCnt]);

			if (GetTickCount() - DeathAnimationBeginTime >= DeathAnimationElapsedTime)
			{
				DeathAnimationCnt++;
				if (DeathAnimationCnt == 1)
				{
					EnemyB.px = px - 10;
					EnemyB.py = py + 65;
				}

				else if (DeathAnimationCnt == 2)
				{
					EnemyB.px = px - 20;
					EnemyB.py = py + 40;
				}
				else if (DeathAnimationCnt == 3)
				{
					EnemyB.px = px - 30;
					EnemyB.py = py + 100;
				}
				else if (DeathAnimationCnt == 4)
				{
					EnemyB.px = px - 40;
					EnemyB.py = py + 130;
				}

				if (DeathAnimationCnt > 4)
				{
					DeathAnimationCnt = 0;
					EnemyB.flag = FirstStageEnd;
					EnemyB.py = 2000;
				}
				DeathAnimationBeginTime = 0;
			}
		}
	}
}

void EnemyBWasAttackByHannahCheck()
{
	if (GameStatus == FirstStage || GameStatus==SecondStage)
	{
		if (Hannah.status == AttackPosture && HannahAttackPostureFirstCnt == 1)
		{
			if (Hannah.HorizontalDirection == left)
			{
				if (EnemyB.px <= Hannah.px - 90 + 92 && EnemyB.px + 87 >= Hannah.px - 90 && EnemyB.py <= Hannah.py + 10 + 23 && EnemyB.py + 127 >= Hannah.py + 10)
				{
					EnemyB.status = WasKonckedDown;
					EnemyB.WasAttackDirection = right;
					if (EnemyB.life >= 5)
						EnemyB.life -= 5;
					if (EnemyB.life <= 0 && EnemyB.status != DeathPosture)
					{
						EnemyB.status = DeathPosture;
						int x = rand() % 4;
						Food.status = x;
						Food.px = EnemyB.px;
						Food.py = EnemyB.py + 150;
					}
				}
			}

			else if (Hannah.HorizontalDirection == right)
			{
				if (EnemyB.px <= Hannah.px + 76 + 100 && EnemyB.px + 96 >= Hannah.px + 76 && EnemyB.py <= Hannah.py + 10 + 14 && EnemyB.py + 145 >= Hannah.py + 10)
				{
					EnemyB.status = WasKonckedDown;
					EnemyB.WasAttackDirection = left;
					if (EnemyB.life >= 5)
						EnemyB.life -= 5;
					if (EnemyB.life <= 0 && EnemyB.status != DeathPosture)
					{
						EnemyB.status = DeathPosture;
						int x = rand() % 4;
						Food.status = x;
						Food.px = EnemyB.px;
						Food.py = EnemyB.py + 150;
					}
				}
			}
		}
	}
}

void HannahWasAttackByEnemyBCheck()
{
	if (GameStatus == FirstStage||GameStatus == SecondStage)
	{
		if (EnemyB.status == AttackPosture && EnemyBAttackPosturetCnt == 2)
		{
			if (EnemyB.HorizontalDirection == left)
			{
				if (EnemyB.px - 90 <= Hannah.px + 80 && EnemyB.px + 92 - 90 >= Hannah.px && EnemyB.py + 10 <= Hannah.py + 151 && EnemyB.py + 10 + 19 >= Hannah.py)
				{
					Hannah.status = WasKonckedDown;
					Hannah.WasAttackDirection = right;
					StillBeginTime = 0;
					if (Hannah.life >= 3)
						Hannah.life -= 3;
					if (Hannah.life <= 0)
						Hannah.status = DeathPosture;
				}
			}

			else if (EnemyB.HorizontalDirection == right)
			{
				if (EnemyB.px + 130 <= Hannah.px + 91 && EnemyB.px + 130 + 87 >= Hannah.px && EnemyB.py + 10 <= Hannah.py + 154 && EnemyB.py + 10 + 21 >= Hannah.py)
				{
					Hannah.status = WasKonckedDown;
					Hannah.WasAttackDirection = left;
					StillBeginTime = 0;
					if (Hannah.life >= 3)
						Hannah.life -= 3;
					if (Hannah.life <= 0)
						Hannah.status = DeathPosture;
				}
			}
		}
	}
}

void HannahWasAttackByEnemyCCheck()
{
	if (GameStatus == ThirdStage)
	{
		if (EnemyC.status == CollidePosture)
		{
			if (EnemyC.HorizontalDirection == left)
			{
				if (EnemyC.px <= Hannah.px + 100 && EnemyC.px + 180 >= Hannah.px && EnemyC.py <= Hannah.py + 200 && EnemyC.py + 170 >= Hannah.py && (fabs(Hannah.py - EnemyC.py) <= 10))
				{
					Hannah.status = WasKonckedDown;
					Hannah.WasAttackDirection = right;
					StillBeginTime = 0;
					if (Hannah.life >= 25)
						Hannah.life -= 25;
					if (Hannah.life <= 0)
						Hannah.status = DeathPosture;
				}
			}

			else if (EnemyC.HorizontalDirection == right)
			{
				if (EnemyC.px <= Hannah.px + 100 && EnemyC.px + 180 >= Hannah.px && EnemyC.py <= Hannah.py + 200 && EnemyC.py + 170 >= Hannah.py && (fabs(Hannah.py - EnemyC.py) <= 10))
				{
					Hannah.status = WasKonckedDown;
					Hannah.WasAttackDirection = left;
					StillBeginTime = 0;
					if (Hannah.life >= 25)
						Hannah.life -= 25;
					if (Hannah.life <= 0)
						Hannah.status = DeathPosture;
				}
			}
		}
	}
}

void IsHannahPickUpDropCheck()
{
	if (GameStatus == FirstStage || GameStatus == SecondStage)
	{
		if (Hannah.px <= Food.px + 80 && Hannah.px + 100 >= Food.px && Hannah.py + 200 >= Food.py && Hannah.py <= Food.py + 40)
		{
			Hannah.life = 40000;
			Food.px = -2000;
			Food.py = -2000;
		}
	}
}


//小怪C
static DWORD EnemyCStillBeginTime = 0;
static DWORD EnemyCStillElapsedTime = 5000;

static DWORD EnemyCWasAttackBeginTime = 0;
static DWORD EnemyCWasAttackElapsedTime = 1000;

void EnemyCStatusChange()
{
	if (GameStatus==ThirdStage)
	{
		if (Hannah.px - EnemyC.px >= 100 && EnemyC.status != CollidePosture)
			EnemyC.HorizontalDirection = right;
		else if (Hannah.px - EnemyC.px <= 100 && EnemyC.status != CollidePosture)
			EnemyC.HorizontalDirection = left;

		if (EnemyC.status == TrackPosture)
		{
			if (fabs(EnemyC.py - Hannah.py) <= 10)
				EnemyC.status = CollidePosture;
			else if (fabs(EnemyC.py - Hannah.py) >= 10)
				EnemyC.status = TrackPosture;
		}

		if (EnemyC.distance >= 1000 && EnemyC.status == CollidePosture)
		{
			EnemyC.distance = 0;
			EnemyC.status = StillPosture;
		}

		if (!EnemyCStillBeginTime && EnemyC.status == StillPosture)
			EnemyCStillBeginTime = GetTickCount();

		if (GetTickCount() - EnemyCStillBeginTime >= EnemyCStillElapsedTime && EnemyC.status == StillPosture)
		{
			EnemyC.status = TrackPosture;
			EnemyCStillBeginTime = 0;
		}

		if (EnemyC.status == WasKonckedDown && GetTickCount() - EnemyCWasAttackBeginTime >= EnemyCWasAttackElapsedTime)
		{
			EnemyC.status = CollidePosture;
			EnemyCWasAttackBeginTime = 0;
		}






		if (EnemyC.life <= 0)
			EnemyC.status = DeathPosture;
	}
}

static int EnemyCCollidePosturetCnt = 0;
void EnemyCPostureAnimationShow()
{
	if (GameStatus==ThirdStage)
	{
		//防卫
		if (EnemyC.status == DefensivePosture)
		{
			if (EnemyC.HorizontalDirection == left)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCDefensiveImgLeft);

			else if (EnemyC.HorizontalDirection == right)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCDefensiveImgRight);
		}

		//静止
		else if (EnemyC.status == StillPosture)
		{
			static int StillPostureCnt = 0;
			static DWORD StillPostureBeginTime = 0;
			DWORD StillPostureElapsedTime = 250;

			if (EnemyC.HorizontalDirection == left)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCStillImgLeft[StillPostureCnt]);
			else if (EnemyC.HorizontalDirection == right)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCStillImgRight[StillPostureCnt]);
			if (!StillPostureBeginTime)
				StillPostureBeginTime = GetTickCount();
			if (GetTickCount() - StillPostureBeginTime >= StillPostureElapsedTime)
			{
				StillPostureCnt++;
				if (StillPostureCnt > 8)
				{
					StillPostureCnt = 0;
				}
				StillPostureBeginTime = 0;
			}
		}


		//追踪主角
		else if (EnemyC.status == TrackPosture)
		{
			static int TrackHannahCnt = 0;
			static DWORD TrackHannahBeginTime = 0;
			DWORD TrackHannahElapsedTime = 100;

			if (!EnemyC.BeginTime)
				EnemyC.BeginTime = GetTickCount();

			if (EnemyC.HorizontalDirection == left)
			{
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCWalkImgLeft[TrackHannahCnt]);
				if (!TrackHannahBeginTime)
					TrackHannahBeginTime = GetTickCount();
				if (GetTickCount() - TrackHannahBeginTime >= TrackHannahElapsedTime)
				{
					TrackHannahCnt++;
					if ((Hannah.py - EnemyC.py) >= 0)
						EnemyC.py += 3;
					else if((Hannah.py - EnemyC.py) <= 0)
						EnemyC.py -= 3;
					if (TrackHannahCnt > 4)
					{
						TrackHannahCnt = 0;
					}
					TrackHannahBeginTime = 0;
				}
			}

			else if (EnemyC.HorizontalDirection == right)
			{
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCWalkImgRight[TrackHannahCnt]);
				if (!TrackHannahBeginTime)
					TrackHannahBeginTime = GetTickCount();
				if (GetTickCount() - TrackHannahBeginTime >= TrackHannahElapsedTime)
				{
					TrackHannahCnt++;
					if ((Hannah.py - EnemyC.py) >= 0)
						EnemyC.py += 3;
					else if ((Hannah.py - EnemyC.py) <= 0)
						EnemyC.py -= 3;
					if (TrackHannahCnt > 4)
					{
						TrackHannahCnt = 0;
					}
					TrackHannahBeginTime = 0;
				}
			}
		}


		//小怪冲撞
		else if (EnemyC.status == CollidePosture)
		{
			static DWORD CollidePosturetBeginTime = 0;
			DWORD CollidePostureElapsedTime = 100;

			if (EnemyC.HorizontalDirection == left)
			{
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCCollideImgLeft[EnemyCCollidePosturetCnt]);
				if (!CollidePosturetBeginTime)
					CollidePosturetBeginTime = GetTickCount();
				if (GetTickCount() - CollidePosturetBeginTime >= CollidePostureElapsedTime)
				{
					EnemyCCollidePosturetCnt++;
					EnemyC.distance += EnemyC.vx;
					EnemyC.px -= EnemyC.vx;
					{
						if ((EnemyCCollidePosturetCnt > 5))
						{
							EnemyCCollidePosturetCnt = 0;
							CollidePosturetBeginTime = 0;
						}
					}
					CollidePosturetBeginTime = 0;
					EnemyCStillBeginTime = 0;
				}
			}

			if (EnemyC.HorizontalDirection == right)
			{
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCCollideImgRight[EnemyCCollidePosturetCnt]);
				if (!CollidePosturetBeginTime)
					CollidePosturetBeginTime = GetTickCount();
				if (GetTickCount() - CollidePosturetBeginTime >= CollidePostureElapsedTime)
				{
					EnemyCCollidePosturetCnt++;
					EnemyC.distance += EnemyC.vx;
					EnemyC.px += EnemyC.vx;
					{
						if ((EnemyCCollidePosturetCnt > 5))
						{
							EnemyCCollidePosturetCnt = 0;
							CollidePosturetBeginTime = 0;
						}
					}
					CollidePosturetBeginTime = 0;
					EnemyCStillBeginTime = 0;
				}
			}
		}


		//被击倒
		else if (EnemyC.status == WasKonckedDown)
		{

			if (EnemyC.WasAttackDirection == left)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCWasKnockedDownImgLeft[0]);
			else if (EnemyC.WasAttackDirection == right)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCWasKnockedDownImgRight[0]);
		}

		else if (EnemyC.status == DeathPosture)
		{

			static int DeathAnimationCnt = 0;
			static DWORD DeathAnimationBeginTime = 0;
			DWORD DeathAnimationElapsedTime = 250;

			static double px = EnemyC.px;
			static double py = EnemyC.py;

			if (!DeathAnimationCnt)
			{
				px = EnemyC.px;
				py = EnemyC.py;
			}

			if (!DeathAnimationBeginTime)
				DeathAnimationBeginTime = GetTickCount();


			if (EnemyC.WasAttackDirection == left)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCWasKnockedDownImgLeft[DeathAnimationCnt]);
			else if (EnemyC.WasAttackDirection == right)
				transparentimage(NULL, EnemyC.px, EnemyC.py, &EnemyCWasKnockedDownImgRight[DeathAnimationCnt]);

			if (GetTickCount() - DeathAnimationBeginTime >= DeathAnimationElapsedTime)
			{
				DeathAnimationCnt++;
				if (DeathAnimationCnt == 1)
				{
					EnemyC.px = px - 10;
					EnemyC.py = py + 20;
				}

				else if (DeathAnimationCnt == 2)
				{
					EnemyC.px = px - 20;
					EnemyC.py = py + 20;
				}
				else if (DeathAnimationCnt == 3)
				{
					EnemyC.px = px - 30;
					EnemyC.py = py + 60;
				}
				else if (DeathAnimationCnt == 4)
				{
					EnemyC.px = px - 40;
					EnemyC.py = py + 85;
				}

				if (DeathAnimationCnt > 4)
				{
					DeathAnimationCnt = 0;
					EnemyC.flag = FirstStageEnd;
					EnemyC.py = 2000;
				}
				DeathAnimationBeginTime = 0;
			}
		}
	}
}


void EnemyCWasAttackByHannahCheck()
{
	if (GameStatus == FirstStage || GameStatus == SecondStage || GameStatus == ThirdStage)
	{
		if (Hannah.status == AttackPosture && HannahAttackPostureFirstCnt == 1 && EnemyC.status!= CollidePosture )
		{
			if (Hannah.HorizontalDirection == left)
			{
				if (EnemyC.px <= Hannah.px - 90 + 92 && EnemyC.px + 143 >= Hannah.px - 90 && EnemyC.py <= Hannah.py + 10 + 23 && EnemyC.py + 190 >= Hannah.py + 10 )
				{
					EnemyC.status = WasKonckedDown;
					if (!EnemyCWasAttackBeginTime)
						EnemyCWasAttackBeginTime = GetTickCount();
					EnemyC.WasAttackDirection = right;
					if (EnemyC.life >= 80)
						EnemyC.life -= 80;
					if (EnemyC.life <= 0 && EnemyC.status != DeathPosture)
					{
						EnemyC.status = DeathPosture;
						Hannah.status = VictoryPosture;
						int x = rand() % 4;
						Food.status = x;
						Food.px = EnemyC.px;
						Food.py = EnemyC.py + 150;
					}
				}
			}

			else if (Hannah.HorizontalDirection == right)
			{
				if (EnemyC.px <= Hannah.px + 76 + 100 && EnemyC.px + 143 >= Hannah.px + 76 && EnemyC.py <= Hannah.py + 10 + 14 && EnemyC.py + 190 >= Hannah.py + 10)
				{
					EnemyC.status = WasKonckedDown;
					if (!EnemyCWasAttackBeginTime)
						EnemyCWasAttackBeginTime = GetTickCount();
					EnemyC.WasAttackDirection = left;
					if (EnemyC.life >= 80)
						EnemyC.life -= 80;
					if (EnemyC.life <= 0 && EnemyC.status != DeathPosture)
					{
						EnemyC.status = DeathPosture;
						Hannah.status = VictoryPosture;
						int x = rand() % 4;
						Food.status = x;
						Food.px = EnemyC.px;
						Food.py = EnemyC.py + 150;
					}
				}
			}
		}
	}
}







int main(void)
{
	StartUp();
	srand(time(NULL));
	BeginBatchDraw();
	while (true)
	{
		StartMenuShow();
		BackGroundShow();

		HannahInformationShow();
		EnemyAInformationShow();
		EnemyBInformationShow();
		EnemyCInformationShow();

		FirstStageFirstCutsceneShow();
		FirstStageSecondCutsceneShow();
		FirstStageThirdCutsceneShow();

		SecondStageFirstCutsceneShow();
		SecondStageEnemyASpecialPostureShow();
		SecondStageSecondCutsceneShow();

		HannahStatusChange();
		EnemyAStatusChange();
		EnemyBStatusChange();
		EnemyCStatusChange();

		HannahWasAttackByEnemyACheck();
		HannahWasAttackByEnemyBCheck();
		HannahWasAttackByEnemyCCheck();

		EnemyAWasAttackByHannahCheck();
		EnemyBWasAttackByHannahCheck();
		EnemyCWasAttackByHannahCheck();

		EnemyAPostureAnimationShow();
		EnemyBPostureAnimationShow();
		EnemyCPostureAnimationShow();
		HannahPostureAnimationShow();

		DropShow();
		IsHannahPickUpDropCheck();

		GameStatusChange();

		FlushBatchDraw();
	}
	EndBatchDraw();
}