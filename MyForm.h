#pragma once
#include "FileSystem.h"
//#include <vector>

namespace semprojectdsa {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            fileSystem = new FileSystem();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
            if (fileSystem)
            {
                delete fileSystem;
            }
        }

    private:
        FileSystem* fileSystem;
        System::Windows::Forms::Button^ button1;
        System::Windows::Forms::Button^ button2;
        System::Windows::Forms::Button^ button3;
        System::Windows::Forms::Button^ button4;
        System::Windows::Forms::Button^ button5;
        System::Windows::Forms::Button^ button6;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::Label^ label6;
        System::Windows::Forms::TextBox^ textBox1;
        System::Windows::Forms::TextBox^ textBox2;
        System::Windows::Forms::RichTextBox^ richTextBox1;
        System::Windows::Forms::RichTextBox^ richTextBoxFreeSpaces;
        System::Windows::Forms::TextBox^ textBoxFilename1;
        System::Windows::Forms::TextBox^ textBoxFilename2;
        System::Windows::Forms::TextBox^ textBoxFilename3;
        System::Windows::Forms::TextBox^ textBoxFilename4;
        System::Windows::Forms::TextBox^ textBoxStartAddr1;
        System::Windows::Forms::TextBox^ textBoxStartAddr2;
        System::Windows::Forms::TextBox^ textBoxStartAddr3;
        System::Windows::Forms::TextBox^ textBoxStartAddr4;
        System::Windows::Forms::TextBox^ textBoxContent1;
        System::Windows::Forms::TextBox^ textBoxContent2;
        System::Windows::Forms::TextBox^ textBoxContent3;
        System::Windows::Forms::TextBox^ textBoxContent4;
    //    System::fiddler
            System::Windows::Forms::TextBox^ textBoxEndAddr1;
        System::Windows::Forms::TextBox^ textBoxEndAddr2;
        System::Windows::Forms::TextBox^ textBoxEndAddr3;
        System::Windows::Forms::TextBox^ textBoxEndAddr4;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->button6 = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
            this->richTextBoxFreeSpaces = (gcnew System::Windows::Forms::RichTextBox());
            this->textBoxFilename1 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxFilename2 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxFilename3 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxFilename4 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxStartAddr1 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxStartAddr2 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxStartAddr3 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxStartAddr4 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxContent1 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxContent2 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxContent3 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxContent4 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxEndAddr1 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxEndAddr2 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxEndAddr3 = (gcnew System::Windows::Forms::TextBox());
            this->textBoxEndAddr4 = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(23, 450);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(127, 36);
            this->button1->TabIndex = 0;
            this->button1->Text = L"Add File";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(170, 450);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(118, 36);
            this->button2->TabIndex = 1;
            this->button2->Text = L"List Files";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
            // 
            // button3
            // 
            this->button3->Location = System::Drawing::Point(306, 450);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(190, 36);
            this->button3->TabIndex = 2;
            this->button3->Text = L"Copy from Windows";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
            // 
            // button4
            // 
            this->button4->Location = System::Drawing::Point(514, 450);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(127, 36);
            this->button4->TabIndex = 3;
            this->button4->Text = L"Delete File";
            this->button4->UseVisualStyleBackColor = true;
            this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
            // 
            // button5
            // 
            this->button5->Location = System::Drawing::Point(23, 502);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(127, 36);
            this->button5->TabIndex = 4;
            this->button5->Text = L"Modify File";
            this->button5->UseVisualStyleBackColor = true;
            this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
            // 
            // button6
            // 
            this->button6->Location = System::Drawing::Point(170, 502);
            this->button6->Name = L"button6";
            this->button6->Size = System::Drawing::Size(190, 36);
            this->button6->TabIndex = 5;
            this->button6->Text = L"Copy to Windows";
            this->button6->UseVisualStyleBackColor = true;
            this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(41, 32);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(158, 24);
            this->label1->TabIndex = 6;
            this->label1->Text = L"File name or Path";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(41, 114);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(192, 24);
            this->label2->TabIndex = 7;
            this->label2->Text = L"File content or File list";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(41, 190);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(144, 24);
            this->label3->TabIndex = 10;
            this->label3->Text = L"Destination Path";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(41, 270);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(144, 24);
            this->label4->TabIndex = 12;
            this->label4->Text = L"Recent Files";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(750, 32);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(144, 24);
            this->label5->TabIndex = 13;
            this->label5->Text = L"Free Spaces";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(750, 270);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(144, 24);
            this->label6->TabIndex = 14;
            this->label6->Text = L"File Details";
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(263, 29);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(441, 29);
            this->textBox1->TabIndex = 8;
            // 
            // textBox2
            // 
            this->textBox2->Location = System::Drawing::Point(263, 187);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(441, 29);
            this->textBox2->TabIndex = 11;
            // 
            // richTextBox1
            // 
            this->richTextBox1->Location = System::Drawing::Point(263, 90);
            this->richTextBox1->Name = L"richTextBox1";
            this->richTextBox1->Size = System::Drawing::Size(441, 71);
            this->richTextBox1->TabIndex = 9;
            this->richTextBox1->Text = L"";
            // 
            // richTextBoxFreeSpaces
            // 
            this->richTextBoxFreeSpaces->Location = System::Drawing::Point(750, 90);
            this->richTextBoxFreeSpaces->Name = L"richTextBoxFreeSpaces";
            this->richTextBoxFreeSpaces->Size = System::Drawing::Size(200, 150);
            this->richTextBoxFreeSpaces->TabIndex = 15;
            this->richTextBoxFreeSpaces->Text = L"";
            // 
            // textBoxFilename1
            // 
            this->textBoxFilename1->Location = System::Drawing::Point(263, 300);
            this->textBoxFilename1->Name = L"textBoxFilename1";
            this->textBoxFilename1->Size = System::Drawing::Size(200, 29);
            this->textBoxFilename1->TabIndex = 16;
            this->textBoxFilename1->ReadOnly = true;
            // 
            // textBoxFilename2
            // 
            this->textBoxFilename2->Location = System::Drawing::Point(263, 340);
            this->textBoxFilename2->Name = L"textBoxFilename2";
            this->textBoxFilename2->Size = System::Drawing::Size(200, 29);
            this->textBoxFilename2->TabIndex = 17;
            this->textBoxFilename2->ReadOnly = true;
            // 
            // textBoxFilename3
            // 
            this->textBoxFilename3->Location = System::Drawing::Point(263, 380);
            this->textBoxFilename3->Name = L"textBoxFilename3";
            this->textBoxFilename3->Size = System::Drawing::Size(200, 29);
            this->textBoxFilename3->TabIndex = 18;
            this->textBoxFilename3->ReadOnly = true;
            // 
            // textBoxFilename4
            // 
            this->textBoxFilename4->Location = System::Drawing::Point(263, 420);
            this->textBoxFilename4->Name = L"textBoxFilename4";
            this->textBoxFilename4->Size = System::Drawing::Size(200, 29);
            this->textBoxFilename4->TabIndex = 19;
            this->textBoxFilename4->ReadOnly = true;
            // 
            // textBoxStartAddr1
            // 
            this->textBoxStartAddr1->Location = System::Drawing::Point(470, 300);
            this->textBoxStartAddr1->Name = L"textBoxStartAddr1";
            this->textBoxStartAddr1->Size = System::Drawing::Size(100, 29);
            this->textBoxStartAddr1->TabIndex = 20;
            this->textBoxStartAddr1->ReadOnly = true;
            // 
            // textBoxStartAddr2
            // 
            this->textBoxStartAddr2->Location = System::Drawing::Point(470, 340);
            this->textBoxStartAddr2->Name = L"textBoxStartAddr2";
            this->textBoxStartAddr2->Size = System::Drawing::Size(100, 29);
            this->textBoxStartAddr2->TabIndex = 21;
            this->textBoxStartAddr2->ReadOnly = true;
            // 
            // textBoxStartAddr3
            // 
            this->textBoxStartAddr3->Location = System::Drawing::Point(470, 380);
            this->textBoxStartAddr3->Name = L"textBoxStartAddr3";
            this->textBoxStartAddr3->Size = System::Drawing::Size(100, 29);
            this->textBoxStartAddr3->TabIndex = 22;
            this->textBoxStartAddr3->ReadOnly = true;
            // 
            // textBoxStartAddr4
            // 
            this->textBoxStartAddr4->Location = System::Drawing::Point(470, 420);
            this->textBoxStartAddr4->Name = L"textBoxStartAddr4";
            this->textBoxStartAddr4->Size = System::Drawing::Size(100, 29);
            this->textBoxStartAddr4->TabIndex = 23;
            this->textBoxStartAddr4->ReadOnly = true;
            // 
            // textBoxContent1
            // 
            this->textBoxContent1->Location = System::Drawing::Point(750, 300);
            this->textBoxContent1->Name = L"textBoxContent1";
            this->textBoxContent1->Size = System::Drawing::Size(200, 29);
            this->textBoxContent1->TabIndex = 24;
            this->textBoxContent1->ReadOnly = true;
            // 
            // textBoxContent2
            // 
            this->textBoxContent2->Location = System::Drawing::Point(750, 340);
            this->textBoxContent2->Name = L"textBoxContent2";
            this->textBoxContent2->Size = System::Drawing::Size(200, 29);
            this->textBoxContent2->TabIndex = 25;
            this->textBoxContent2->ReadOnly = true;
            // 
            // textBoxContent3
            // 
            this->textBoxContent3->Location = System::Drawing::Point(750, 380);
            this->textBoxContent3->Name = L"textBoxContent3";
            this->textBoxContent3->Size = System::Drawing::Size(200, 29);
            this->textBoxContent3->TabIndex = 26;
            this->textBoxContent3->ReadOnly = true;
            // 
            // textBoxContent4
            // 
            this->textBoxContent4->Location = System::Drawing::Point(750, 420);
            this->textBoxContent4->Name = L"textBoxContent4";
            this->textBoxContent4->Size = System::Drawing::Size(200, 29);
            this->textBoxContent4->TabIndex = 27;
            this->textBoxContent4->ReadOnly = true;
            // 
            // textBoxEndAddr1
            // 
            this->textBoxEndAddr1->Location = System::Drawing::Point(960, 300);
            this->textBoxEndAddr1->Name = L"textBoxEndAddr1";
            this->textBoxEndAddr1->Size = System::Drawing::Size(100, 29);
            this->textBoxEndAddr1->TabIndex = 28;
            this->textBoxEndAddr1->ReadOnly = true;
            // 
            // textBoxEndAddr2
            // 
            this->textBoxEndAddr2->Location = System::Drawing::Point(960, 340);
            this->textBoxEndAddr2->Name = L"textBoxEndAddr2";
            this->textBoxEndAddr2->Size = System::Drawing::Size(100, 29);
            this->textBoxEndAddr2->TabIndex = 29;
            this->textBoxEndAddr2->ReadOnly = true;
            // 
            // textBoxEndAddr3
            // 
            this->textBoxEndAddr3->Location = System::Drawing::Point(960, 380);
            this->textBoxEndAddr3->Name = L"textBoxEndAddr3";
            this->textBoxEndAddr3->Size = System::Drawing::Size(100, 29);
            this->textBoxEndAddr3->TabIndex = 30;
            this->textBoxEndAddr3->ReadOnly = true;
            // 
            // textBoxEndAddr4
            // 
            this->textBoxEndAddr4->Location = System::Drawing::Point(960, 420);
            this->textBoxEndAddr4->Name = L"textBoxEndAddr4";
            this->textBoxEndAddr4->Size = System::Drawing::Size(100, 29);
            this->textBoxEndAddr4->TabIndex = 31;
            this->textBoxEndAddr4->ReadOnly = true;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1100, 600);
            this->Controls->Add(this->textBoxEndAddr4);
            this->Controls->Add(this->textBoxEndAddr3);
            this->Controls->Add(this->textBoxEndAddr2);
            this->Controls->Add(this->textBoxEndAddr1);
            this->Controls->Add(this->textBoxContent4);
            this->Controls->Add(this->textBoxContent3);
            this->Controls->Add(this->textBoxContent2);
            this->Controls->Add(this->textBoxContent1);
            this->Controls->Add(this->textBoxStartAddr4);
            this->Controls->Add(this->textBoxStartAddr3);
            this->Controls->Add(this->textBoxStartAddr2);
            this->Controls->Add(this->textBoxStartAddr1);
            this->Controls->Add(this->textBoxFilename4);
            this->Controls->Add(this->textBoxFilename3);
            this->Controls->Add(this->textBoxFilename2);
            this->Controls->Add(this->textBoxFilename1);
            this->Controls->Add(this->richTextBoxFreeSpaces);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->richTextBox1);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->button6);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button1);
            this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->Margin = System::Windows::Forms::Padding(6);
            this->Name = L"MyForm";
            this->Text = L"FileSystem";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion
    private:
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button4_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button5_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void button6_Click(System::Object^ sender, System::EventArgs^ e);
        void UpdateFileDisplay(const std::string& filename, int startAddress, const std::string& content, int endAddress);
        void ClearFileDisplay();
    };
}