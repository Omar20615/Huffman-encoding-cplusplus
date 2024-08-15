#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"MyProject.h"
#include<iostream>
#include<Windows.h>
#include<sys/stat.h>
#include<fstream>
#include<cstring>
#include<string>
#include"MyForm.h"
#include<algorithm>
#include<conio.h>
#include<stdio.h>
#include<msclr\marshal_cppstd.h>
#include <Mmsystem.h>
#include <mciapi.h>
//#include<string>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")
huffmanCode b;
std::string name;
namespace DSProjectGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ browseButton;
	private: System::Windows::Forms::Button^ compressButton;
	private: System::Windows::Forms::Button^ decompressButton;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->browseButton = (gcnew System::Windows::Forms::Button());
			this->compressButton = (gcnew System::Windows::Forms::Button());
			this->decompressButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// browseButton
			// 
			this->browseButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->browseButton->Location = System::Drawing::Point(159, 105);
			this->browseButton->Name = L"browseButton";
			this->browseButton->Size = System::Drawing::Size(189, 63);
			this->browseButton->TabIndex = 0;
			this->browseButton->Text = L"Browse File";
			this->browseButton->UseVisualStyleBackColor = true;
			this->browseButton->Click += gcnew System::EventHandler(this, &MyForm::BrowseButton_Click);
			// 
			// compressButton
			// 
			this->compressButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->compressButton->Location = System::Drawing::Point(38, 129);
			this->compressButton->Name = L"compressButton";
			this->compressButton->Size = System::Drawing::Size(189, 63);
			this->compressButton->TabIndex = 1;
			this->compressButton->Text = L"Compress";
			this->compressButton->UseVisualStyleBackColor = true;
			this->compressButton->Visible = false;
			this->compressButton->Click += gcnew System::EventHandler(this, &MyForm::CompressButton_Click);
			// 
			// decompressButton
			// 
			this->decompressButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->decompressButton->Location = System::Drawing::Point(268, 129);
			this->decompressButton->Name = L"decompressButton";
			this->decompressButton->Size = System::Drawing::Size(189, 63);
			this->decompressButton->TabIndex = 2;
			this->decompressButton->Text = L"Decompress";
			this->decompressButton->UseVisualStyleBackColor = true;
			this->decompressButton->Visible = false;
			this->decompressButton->Click += gcnew System::EventHandler(this, &MyForm::DecompressButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(492, 340);
			this->Controls->Add(this->decompressButton);
			this->Controls->Add(this->compressButton);
			this->Controls->Add(this->browseButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
		
		
	private: System::Void OpenFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	private: System::Void BrowseButton_Click(System::Object^ sender, System::EventArgs^ e) {
		browseButton->Visible = false;
		openFileDialog1->InitialDirectory = "D:\\Courses\\Semester 4\\Data Structure\\Lab Codes\\Project\\DS Project GUI\\DS Project GUI";
		openFileDialog1->Title = "Select a file : ";
		openFileDialog1->FileName = "";
		//openFileDialog1->Filter = "txt files (*.txt)|*.txt|*.txt|All files (*.*)|*.*";
		if (openFileDialog1->ShowDialog() != Windows::Forms::DialogResult::Cancel)
		{
			msclr::interop::marshal_context context;
			name = context.marshal_as<std::string>(openFileDialog1->FileName);

		}
		compressButton->Visible = true;
		decompressButton->Visible = true;
		
	}
	private: System::Void CompressButton_Click(System::Object^ sender, System::EventArgs^ e) {
		b.insert(name);
		b.binarycode();
		
	}
private: System::Void DecompressButton_Click(System::Object^ sender, System::EventArgs^ e) {
	b.printdecode();
	compressButton->Visible = false;
	decompressButton->Visible = false;
	browseButton->Visible = true;

}
private: System::Void TextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	 
	
}
};
}