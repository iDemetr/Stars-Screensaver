#include "Star.h"
#include <iostream>

#pragma once

namespace Stars
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		cli::array<Star^>^ Stars;																	//������ ������ ������

		Graphics^ graphics;
		Random random;

		int NumberStars = 5000;																		//����������� �����.

		int pW;																						//������ ������.
		int pH;																						//������ ������.

		int Speed;
		float StarSize;

		//����������� �����
		MyForm()
		{
			InitializeComponent();

			Stars = gcnew array<Star^>(NumberStars);

			Speed = 13;
		}

	protected:

		~MyForm() { if (components) { delete components; } }

	private:
		System::Windows::Forms::Timer^ timer1;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(284, 259);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(284, 259);
			this->ControlBox = false;
			this->Controls->Add(this->pictureBox1);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Stars";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		//--------------------------------------------------------------------------------------------------------------------------------------

	private:

		float Map(float n, float start1, float start2, float stop1, float stop2)
		{
			return((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
		}

		//������������� ������.
		System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e)
		{
			pW = pictureBox1->Width;																//������ ������.
			pH = pictureBox1->Height;																//������ ������.

			//��������� ������������� ����� �� ������
			for (int i = 0; i < NumberStars; i++)
			{
				Stars[i] = gcnew Star;
				{
					Stars[i]->X = random.Next(-pW / 3, pW / 3);
					Stars[i]->Y = random.Next(-pH / 2, pH / 2);
					Stars[i]->Z = random.Next(10, pW);
				}
			}

			pictureBox1->Image = gcnew Bitmap(pW, pH);
			graphics = Graphics::FromImage(pictureBox1->Image);

			timer1->Start();
		}

		//���������� ����� �� ������.
		System::Void DrawStar(array<Star^>^ Stars, int i)
		{
			StarSize = Map(Stars[i]->Z, 0, 8, pW, 0);												//������ �����.

			float x = Map(Stars[i]->X / Stars[i]->Z, 0, 0, 1, pW) + pW / 2;
			float y = Map(Stars[i]->Y / Stars[i]->Z, 0, 0, 1, pH) + pH / 2;

			if (Stars[i]->Z < 1000)
			{
				graphics->FillEllipse(Brushes::YellowGreen, x, y, StarSize, StarSize);				//���������� �����.
			}
			else
				graphics->FillEllipse(Brushes::LightGreen, x, y, StarSize, StarSize);				//���������� �����.
		}

		//�������� ����� �� ������.
		System::Void MoveStar(array<Star^>^ Stars, int i)
		{
			Stars[i]->Z -= Speed;																	//�������� ����� ����.

			if (Stars[i]->Z < 1)
			{
				Stars[i]->X = random.Next(-pW / 3, pW / 3);
				Stars[i]->Y = random.Next(-pH / 2, pH / 2);
				Stars[i]->Z = random.Next(10, pW);
			}
		}

		//������
		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			graphics->Clear(Color::Black);															//���������� ����� ������.

			for (int i = 0; i < NumberStars; i++)
			{
				DrawStar(Stars, i);																	//���������� ����� �� ������.
				MoveStar(Stars, i);																	//����������� ���� �� ������.
			}

			pictureBox1->Refresh();																	//�������� �����.
		}

		//����������� ������� �������.
		System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{

			if (e->KeyCode == Keys::Space)
			{
				if (timer1->Enabled)
				{
					timer1->Stop();																	//���������� �������� ����.
				}
				else
				{
					timer1->Start();																//����������� �������� ����.
				}
			}
			else
				if (e->KeyCode == Keys::Escape)														//������� ����� ��� ������� Escape.
				{
					Close();
				}
			if (e->KeyCode == Keys::Up)
			{
				Speed += 5;
			}
			else
				if (e->KeyCode == Keys::Down)
				{
					Speed -= 5;
				}
		}
	};
}
