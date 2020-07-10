#pragma once
#include "Pos.h"
namespace cppsnake {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	public: System::Windows::Forms::Panel^ Panel1;
	public: System::Windows::Forms::Button^ ButtonStart;
	public: System::Windows::Forms::Timer^ Timer1;
	public: System::Windows::Forms::Timer^ Timer2;
	public: array<array<System::Windows::Forms::Label^>^>^ Label1;
	public: static int MapWidth=10;
	public: static int MapHeight=10;
	public: array<array<int^>^>^ c; //int c[MapHeight-1][MapWidth-1];
	public: static double TimeStep=1.05;
	public: static int MinInterval=100;
	public: static bool GameStart=false;
	public: static long score=0;
	public: static int Mode=1;
	public: static int Mode2Setting=1;
	public: Pos^ TargetPos;
	public: array<Pos^>^ snake;//(MapWidth * MapHeight - 1)
	public: static int snakeLen;
	public: static int HeadDirection;
	
	
	
	public: System::Void ButtonStart_Click(System::Object^ sender, System::EventArgs^ e){
				ReLoad();
			}

	public: bool PosOccupy1(int x,int y){
				if (snakeLen<=4) {return false;}
				for (int i=2;i<=snakeLen-1;i+=1){
					if ((snake[i]->x == x) && (snake[i]->y == y)) {return true;}
				}
				return false;
			}

	public: System::Void Timer1_Tick(System::Object^ sender, System::EventArgs^ e){
				bool GameOver = false;
				bool Eat=false;
				switch (HeadDirection){
				case(37)://L
					{
						if (snake[0]->x==1) {GameOver = Game_Over();}
						if (PosOccupy1(snake[0]->x-1,snake[0]->y)) {GameOver = Game_Over();}
						if (GameOver) {return;}
						if ((snake[0]->x-1==TargetPos->x) && (snake[0]->y==TargetPos->y)) {Eat=true;}
					}
					break;
				case (38)://U
					{
						if (snake[0]->y==1) {GameOver = Game_Over();}
						if (PosOccupy1(snake[0]->x,snake[0]->y-1)) {GameOver = Game_Over();}
						if (GameOver) {return;}
						if ((snake[0]->x==TargetPos->x) && (snake[0]->y-1==TargetPos->y)) {Eat=true;}
					}
					break;
				case (39)://R
					{
						if (snake[0]->x==MapWidth) {GameOver = Game_Over();}
						if (PosOccupy1(snake[0]->x+1,snake[0]->y)) {GameOver = Game_Over();}
						if (GameOver) {return;}
						if ((snake[0]->x+1==TargetPos->x) && (snake[0]->y==TargetPos->y)) {Eat=true;}
					
					}
					break;
				case (40)://D
					{
						if (snake[0]->y==MapHeight) {GameOver = Game_Over();}
						if (PosOccupy1(snake[0]->x,snake[0]->y+1)) {GameOver = Game_Over();}
						if (GameOver) {return;}
						if ((snake[0]->x==TargetPos->x) && (snake[0]->y+1==TargetPos->y)) {Eat=true;}
					
					}
					break;
				}
				Label1[snake[0]->y-1][snake[0]->x-1]->BackColor = System::Drawing::Color::Blue;
				switch (Mode){
				case (1):
					{
						if (Eat) {snake[snakeLen]->x=snake[snakeLen-1]->x;snake[snakeLen]->y=snake[snakeLen-1]->y;}
						if (!Eat) {Label1[snake[snakeLen - 1]->y - 1][snake[snakeLen - 1]->x - 1]->BackColor = System::Drawing::Color::White;}
						for (int i=snakeLen;i>=1;i-=1) {snake[i]->x=snake[i-1]->x;snake[i]->y=snake[i-1]->y;}
						if (Eat) {snakeLen+=1;}
					}
					break;
				case (2):
					{
						if (!Eat) {snake[snakeLen]->x=snake[snakeLen-1]->x;snake[snakeLen]->y=snake[snakeLen-1]->y;}
						if (Eat) {Label1[snake[snakeLen-1]->y-1][snake[snakeLen-1]->x-1]->BackColor = System::Drawing::Color::White;}
						for (int i=snakeLen-1;i>=1;i-=1){snake[i]=snake[i-1];}
						if (!Eat) {snakeLen+=1;}
						if (Eat) {
							for (int i=1;i<=Mode2Setting;i+=1)
							{
								if (snakeLen==1) {break;}
								Label1[snake[snakeLen-1]->y-1][snake[snakeLen-1]->x-1]->BackColor = System::Drawing::Color::White;
								snakeLen-=1;
							}
						}
					}
					break;
				}
				if (HeadDirection != 40){snake[0]->x+=HeadDirection-38;}
				if (HeadDirection != 37){snake[0]->y+=HeadDirection-39;}
				Label1[snake[0]->y-1][snake[0]->x-1]->BackColor = System::Drawing::Color::Purple;
				if(Eat){CreateNewItem();}
				if(Eat){Timer1->Interval /=TimeStep;}
				if(Eat){score+=100;}
				if(Timer1->Interval < MinInterval){Timer1->Interval = MinInterval;}
			}
	public: System::String^ GetDir(int i){
				switch (i){
				case (37):
					{
						return "L";
					}
					break;
				case (38):
					{
						return "U";
					}
					break;
				case (39):
					{
						return "R";
					}
					break;
				case (40):
					{
						return "D";
					}
					break;
				}
				return "NULL";
			}
	public: bool Game_Over(){
				GameStart = false;
				Timer1->Enabled = false;
				Timer2->Enabled = false;
				MessageBox::Show("Game Over! Score=" + Convert::ToString(score));
				return true;
			}

	public: System::Void CreateNewItem(){
				Pos^ p=gcnew Pos();
				if (snakeLen==MapHeight*MapWidth){return;}
				array<array<bool^>^>^ k=(gcnew array<array<bool^>^>(MapHeight+1));
				for (int i=0;i<=MapHeight;i+=1){
					k[i]=(gcnew array<bool^>(MapWidth+1)); 
					for (int j=0;j<=MapWidth;j+=1){k[i][j]=(gcnew bool);}
				}
				
				array<Pos^>^ q =(gcnew array<Pos^>(MapHeight*MapWidth+1));
				for (int i=0;i<=MapHeight*MapWidth;i+=1){q[i]=gcnew Pos();}
				
				int qlen=0;
				for (int i=1;i<=MapHeight;i+=1)
				{
					for (int j=1;j<=MapWidth;j+=1)
					{
						k[i][j]=true;
					}
				}
				for (int i=0;i<MapHeight*MapWidth;i+=1)
				{
					k[snake[i]->y][snake[i]->x]=false;
				}
				for(int i=1;i<=MapHeight;i+=1)
				{
					for (int j=1;j<=MapWidth;j+=1)
					{
						if (*k[i][j]){
							qlen+=1;
							q[qlen]->y=i;
							q[qlen]->x=j;
						}
					}
				}
				if (qlen==0){return;}
				System::Random^ RanInt = (gcnew System::Random());
				int t=RanInt->Next(1,qlen+1);
				p->x = q[t]->x; p->y=q[t]->y;
				TargetPos->x = p->x;
				TargetPos->y = p->y;
				Label1[p->y-1][p->x-1]->BackColor = System::Drawing::Color::Red;
			}

	public: System::Void ReLoad(){
				this->SuspendLayout();
				this->Text = "Snake";
				this->Height = 130+15*MapHeight;
				this->Width = 55+15*MapWidth;
				delete (ButtonStart);
				delete (Label1);
				delete (Panel1);
				
				ButtonStart = (gcnew System::Windows::Forms::Button());
				ButtonStart->Parent = this;
				ButtonStart->Top = 30+15*MapHeight;
				ButtonStart->Left = this->Width/2-40;
				ButtonStart->Width=80;
				ButtonStart->Height = 40;
				ButtonStart->Text = "Start";
				ButtonStart->BackColor = System::Drawing::SystemColors::Control;
				
				Panel1 = (gcnew System::Windows::Forms::Panel());
				Panel1->Parent = this;
				Panel1->Top =20;
				Panel1->Left = 20;
				Panel1->Width=40+15*MapWidth;
				Panel1->Height = 40+15*MapHeight;
				ButtonStart->Click += (gcnew System::EventHandler(this,&Form1::ButtonStart_Click));
				//ReDim Label1(MapHeight - 1, MapWidth - 1)
				Label1 = gcnew array<array<System::Windows::Forms::Label^>^>(MapHeight);
				for (int i=0;i<=MapHeight-1;i+=1)
				{
					Label1[i] = gcnew array<System::Windows::Forms::Label^>(MapWidth);
				}
				//ReDim c(MapHeight - 1, MapWidth - 1)
				c = gcnew array<array<int^>^>(MapHeight);
				for (int i=0;i<=MapHeight-1;i+=1)
				{
					c[i] = gcnew array<int^>(MapWidth);
					for (int j=0;j<=MapWidth-1;j+=1){c[i][j]=gcnew int;}
				}
				//ReDim snake(MapHeight * MapWidth - 1)
				snake = gcnew array<Pos^>(MapHeight*MapWidth);
				for (int j=0;j<=MapHeight*MapWidth-1;j+=1){snake[j]=gcnew Pos;}
				Timer2->Enabled = false;
				score=0;
				snakeLen=1;
				snake[0]->x = MapWidth/2;
				snake[0]->y = MapHeight/2;
				HeadDirection = 39;
				Timer1->Interval = 750;
				for (int i=0;i<=MapHeight-1;i+=1)
				{
					for (int j=0;j<=MapWidth-1;j+=1)
					{
						
						Label1[i][j] = (gcnew System::Windows::Forms::Label());
						Label1[i][j]->Parent = Panel1;
						Label1[i][j]->Top=i*15;
						Label1[i][j]->Left = j*15;
						Label1[i][j]->Height = 15;
						Label1[i][j]->Width = 15;
						Label1[i][j]->BorderStyle =System::Windows::Forms::BorderStyle::FixedSingle;
						Label1[i][j]->BackColor = System::Drawing::Color::White;

					}
				}
				Panel1->ResumeLayout();
				this->ResumeLayout();
				CreateNewItem();
				Timer1->Enabled = true;
				GameStart=true;
				this->Text = "Snake Score=" + Convert::ToString(score) + " Interval=" + Convert::ToString(Timer1->Interval) + " Dir=" + GetDir(HeadDirection);
				if (!Timer1->Enabled) {this->Text += " 已暂停";}
			}

	public: System::Void Form_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e){
				if (Convert::ToString(e->KeyCode)->ToLower()=="h"){
					GameStart = true;
					MessageBox::Show("Cheat On!");
				}
				if (Convert::ToString(e->KeyCode)->ToLower()=="m"){
				System::Windows::Forms::Form^ form2;
				form2 = (gcnew System::Windows::Forms::Form());
				form2->Height = 150;
				form2->Width = 180;
				System::Windows::Forms::Label^ Label2_1;
				System::Windows::Forms::Label^ Label2_2;
				System::Windows::Forms::Label^ Label2_3;
				Label2_1 = (gcnew System::Windows::Forms::Label());
				Label2_1->Parent = form2;
				Label2_1->Text = "SetHeight";
				Label2_1->Top = 10;
				Label2_1->Width = 60;

				Label2_2 = (gcnew System::Windows::Forms::Label());
				Label2_2->Parent = form2;
				Label2_2->Text = "SetWidth";
				Label2_2->Top = 40;
				Label2_2->Width = 60;

				Label2_3 = (gcnew System::Windows::Forms::Label());
				Label2_3->Parent = form2;
				Label2_3->Text = "SetMode";
				Label2_3->Top = 70;
				Label2_3->Width = 60;

				System::Windows::Forms::TextBox^ TxHeight;
				System::Windows::Forms::TextBox^ TxWidth;
				System::Windows::Forms::TextBox^ TxMode;
				TxHeight = (gcnew System::Windows::Forms::TextBox());
				TxHeight->Parent = form2;
				TxHeight->Top =10;
				TxHeight->Width = 90;
				TxHeight->Left = 60;
				TxHeight->Text = Convert::ToString(MapHeight);

				TxWidth = (gcnew System::Windows::Forms::TextBox());
				TxWidth->Parent = form2;
				TxWidth->Top =40;
				TxWidth->Width = 90;
				TxWidth->Left = 60;
				TxWidth->Text = Convert::ToString(MapWidth);

				TxMode = (gcnew System::Windows::Forms::TextBox());
				TxMode->Parent = form2;
				TxMode->Top =70;
				TxMode->Width = 90;
				TxMode->Left = 60;
				TxMode->Text = Convert::ToString(Mode);

				bool b1=Timer1->Enabled;
				bool b2=Timer2->Enabled;
				Timer1->Enabled = false;
				Timer2->Enabled = false;
				form2->ShowDialog();

				bool b3=true;
				if (MapHeight != Int32::Parse(TxHeight->Text)){b3=false;}
				if (MapWidth != Int32::Parse(TxWidth->Text)){b3=false;}
				if (Mode != Int32::Parse(TxMode->Text)){b3=false;}
				if (Int32::Parse(TxHeight->Text)*Int32::Parse(TxWidth->Text)*Int32::Parse(TxMode->Text)>0){
					MapHeight = Int32::Parse(TxHeight->Text);
					MapWidth = Int32::Parse(TxWidth->Text);
					Mode = Int32::Parse(TxMode->Text);
				}
				else
				{
					b3=true;
				}
				if (!b3){
					ButtonStart_Click(sender,e);
				}else
				{
					Timer1->Enabled=b1;
					Timer2->Enabled=b2;
				}
				this->BackColor = ((Mode==1)?(System::Drawing::SystemColors::Control):(System::Drawing::Color::Black));
				}
				if (!GameStart) return;
				
				if (Convert::ToString(e->KeyCode)->ToLower()=="a")
					{
						if (HeadDirection!=39) HeadDirection=37;
					}
				
				if (Convert::ToString(e->KeyCode)->ToLower()=="w")
					{
						if (HeadDirection!=40) HeadDirection=38;
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="d")
					{
						if (HeadDirection!=37) HeadDirection=39;
					}
					
				if (Convert::ToString(e->KeyCode)->ToLower()=="s")
					{
						if (HeadDirection!=38) HeadDirection=40;
					}
					
				if (Convert::ToString(e->KeyCode)->ToLower()=="p")
					{
						Timer1->Enabled = !(Timer1->Enabled);
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="r")
					{
						Timer1_Tick(sender,e);
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="q")
					{
						Timer1->Interval *=1.05;
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="e")
					{
						Timer1->Interval /=1.05;
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="j")
					{
						HeadDirection = 37;
						Timer1_Tick(sender,e);
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="i")
					{
						HeadDirection = 38;
						Timer1_Tick(sender,e);
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="k")
					{
						HeadDirection = 40;
						Timer1_Tick(sender,e);
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="l")
					{
						HeadDirection = 39;
						Timer1_Tick(sender,e);
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="c")
					{
						if ((MapWidth == MapHeight) && (MapWidth%2==0)){
							int n=MapWidth;
							c[0][0]=39;
							c[1][0]=38;
							switch ((n%4)==0){
							case (true):
									{
										c[n/2][n/2-2]=39;
										c[n/2][n/2-1]=39;
										c[n/2+1][n/2-2]=38;
										c[n/2+1][n/2-1]=37;
										for (int i=1;i<=n-3;i+=1){
											c[0][i]=39;
											c[1][i]=37;
										}
										for (int i=2;i<=n/2-2;i+=2){
											c[i][i-2]=39;
											c[i+1][i-2]=38;
											c[i][i-1]=39;
											c[i+1][i-1]=40;
								
											c[n-i][i-1]=39;
											c[n-i+1][i-1]=37;
											c[n-i][i-2]=38;
											c[n-i+1][i-2]=38;
											for (int j=i+2;j<=n-i-1;j+=1){
												c[j][i-2]=38;
												c[j][i-1]=40;
												c[i][j-2]=39;
												c[i+1][j-2]=37;
											}
										}
										for (int i=0;i<=n/2-2;i+=2){
											c[i][n-1-i]=40;
											c[i+1][n-1-i]=40;
											c[i][n-1-i-1]=39;
											c[i+1][n-1-i-1]=37;

											c[n-2-i][n-1-i]=40;
											c[n-2-i+1][n-1-i]=37;
											c[n-2-i][n-1-i-1]=38;
											c[n-2-i+1][n-1-i-1]=37;
											for (int j=i+2;j<=n-3-i;j+=1){
												c[j][n-1-i-1]=38;
												c[j][n-1-i]=40;
												c[n-1-i-1][j]=39;
												c[n-1-i][j]=37;
											}
										}
									}break;
							case (false):
									{
										c[n/2-1][n/2-1]=39;
										c[n/2][n/2-1]=37;
                            
										for (int i=1;i<=n-3;i+=1){
											c[0][i]=39;
											c[1][i]=37;
										}
										for (int i=2;i<=n/2-3;i+=2){
											for (int j=i;j<=n-i-3;j+=1){
												c[i][j]=39;
												c[i+1][j]=37;
												c[n-i][j]=39;
												c[n-i+1][j]=37;
											}
										}
										for (int i=n/2+1;i<=n-2;i+=2){
											c[i][i-2]=39;
											c[i][i-1]=39;
											c[i+1][i-2]=37;
											c[i+1][i-1]=37;
										}
			
										c[n/2-1][n/2]=39;
										c[n/2][n/2]=38;
										for (int i=0;i<=n/2-3;i+=2){
											c[i+2][i]=39;
											c[i+2][i+1]=39;
											c[i+3][i]=38;
											c[i+3][i+1]=40;
			
											c[n-1-i][i]=38;
											c[n-1-i-1][i]=38;
											c[n-1-i][i+1]=37;
											c[n-1-i-1][i+1]=39;
										}
										for (int i=0;i<=n/2-5;i+=2){
											for (int j=i+4;j<=n-i-3;j+=1){
												c[j][i]=38;
												c[j][i+1]=40;
											}
										}
										for (int i=n-1;i>=n/2+1;i-=2){
											c[i][i]=37;
											c[i-1][i]=40;
											c[i][i-1]=37;
											c[i-1][i-1]=38;
											c[n-1-i][i]=40;
											c[n-1-i+1][i]=40;
											c[n-1-i][i-1]=39;
											c[n-1-i+1][i-1]=37;
											for (int j=i-2;j>=n-1-i+2;j-=1){
												c[j][i]=40;
												c[j][i-1]=38;
											}
										}
										c[n/2-1][n/2]=40;
										c[n/2][n/2]=37;
									}break;
							}
						}else{
							c[0][MapWidth-1]=40;
							c[1][0]=38;
							c[MapHeight-1][MapWidth-1]=37;
							for (int i=0;i<=MapWidth-2;i+=1){c[0][i]=39;}
							for (int i=1;i<=MapHeight-2;i+=1){
								for (int j=1;j<=MapWidth-1;j+=2){
									c[i][j]=40;
									c[i+1][j-1]=38;
								}
							}
							for (int i=2;i<=MapWidth-1;i+=2){
								c[1][i]=37;
								c[MapHeight-1][i-1]=37;
							}
						}
						Timer2->Enabled = true;
					}
				if (Convert::ToString(e->KeyCode)->ToLower()=="v")
					{
						Timer2->Enabled=false;
					}
				
			this->Text = "Snake Score=" + Convert::ToString(score) + " Interval=" + Convert::ToString(Timer1->Interval) + "Dir=" + GetDir(HeadDirection);
			if (!Timer1->Enabled) {this->Text+="已暂停";}
			}

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 //ReDim Label1(MapHeight - 1, MapWidth - 1)
			 this->KeyPreview = true;
			 Label1 = gcnew array<array<System::Windows::Forms::Label^>^>(MapHeight);
			 for (int i=0;i<=MapHeight-1;i+=1)
			 {
			 	Label1[i] = gcnew array<System::Windows::Forms::Label^>(MapWidth);
			 }
			 //ReDim c(MapHeight - 1, MapWidth - 1)
				c = gcnew array<array<int^>^>(MapHeight);
			 for (int i=0;i<=MapHeight-1;i+=1)
			 {
			 	c[i] = gcnew array<int^>(MapWidth);
			 }
			 //ReDim snake(MapHeight * MapWidth - 1)
			 snake = gcnew array<Pos^>(MapHeight*MapWidth);
				for (int j=0;j<=MapHeight*MapWidth-1;j+=1){snake[j]=gcnew Pos;}
			 TargetPos=(gcnew Pos());

			 this->SuspendLayout();

			 this->Text = "Snake";
			 this->Height = 130+15*MapHeight;
			 this->Width = 55+15*MapWidth;
			 
			 Timer1 = (gcnew System::Windows::Forms::Timer());Timer1->Interval = 750;Timer1->Enabled = false;
			 Timer2 = (gcnew System::Windows::Forms::Timer());Timer2->Interval = 1;Timer2->Enabled = false;

			 ButtonStart = (gcnew System::Windows::Forms::Button());ButtonStart->Parent = this;ButtonStart->Top=30+15*MapHeight;ButtonStart->Left=this->Width/2-40;ButtonStart->Width=80;ButtonStart->Height=40;ButtonStart->Text="Start";ButtonStart->BackColor = System::Drawing::SystemColors::Control;
			 this->KeyDown += (gcnew System::Windows::Forms::KeyEventHandler(this,&Form1::Form_KeyDown));
			 Panel1 = (gcnew System::Windows::Forms::Panel);Panel1->Parent = this;Panel1->Top=20;Panel1->Left=20;Panel1->Width=40+15*MapWidth;Panel1->Height=40+15*MapHeight;
			 Panel1->SuspendLayout();
			 Timer1->Tick += (gcnew System::EventHandler(this,&Form1::Timer1_Tick));
			 Timer2->Tick += (gcnew System::EventHandler(this,&Form1::Timer2_Tick));
			 ButtonStart->Click += (gcnew System::EventHandler(this,&Form1::ButtonStart_Click));
			 snakeLen=1;
			 snake[0] = (gcnew(Pos));
			 snake[0]->x = MapHeight / 2;
			 snake[0]->y = MapWidth / 2;

			 HeadDirection = 39;
			 for (int i=0;i<=MapHeight-1;i+=1){
				 for (int j=0;j<=MapWidth-1;j+=1){
					 Label1[i][j] = (gcnew System::Windows::Forms::Label());Label1[i][j]->Parent = Panel1;Label1[i][j]->Top=i*15;Label1[i][j]->Left=j*15;Label1[i][j]->Height=15;Label1[i][j]->Width=15;Label1[i][j]->BorderStyle=System::Windows::Forms::BorderStyle::FixedSingle;Label1[i][j]->BackColor = System::Drawing::Color::White;
				 }
			 }
			 this->ResumeLayout();
			 CreateNewItem();
			 GameStart=true;
			 Timer1->Enabled = true;
			 Panel1->ResumeLayout();
			 this->Text = "Snake Score=" + Convert::ToString(score) + " Interval=" + Convert::ToString(Timer1->Interval) + " Dir=" + GetDir(HeadDirection);
			 if (!Timer1->Enabled) {this->Text+=" 已暂停";}
			 }
		
public: System::Void Timer2_Tick(System::Object^ sender,System::EventArgs^ e){
			HeadDirection = *c[snake[0]->y-1][snake[0]->x-1];
			switch (HeadDirection){
			case(37):
				{
					this->BackColor = System::Drawing::Color::Cyan;
				}break;
			case(38):
				{
					this->BackColor = System::Drawing::Color::Magenta;
				}break;
			case(39):
				{
					this->BackColor = System::Drawing::Color::Yellow;
				}break;
			case(40):
				{
					this->BackColor = System::Drawing::Color::Black;
				}break;
			}
			Form_KeyDown(sender,(gcnew System::Windows::Forms::KeyEventArgs(System::Windows::Forms::Keys::R)));
		}
	};
}