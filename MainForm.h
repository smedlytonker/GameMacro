#pragma once

#include "Common.h"
#include "MacroKeyForm.h"

namespace GameMacro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^ macroList;
	private: System::Windows::Forms::Button^ addMacro;
	protected:

	protected:

	private: System::Windows::Forms::ColumnHeader^ columnkeyCode;
	private: System::Windows::Forms::ColumnHeader^ columnKeyName;

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
			this->macroList = (gcnew System::Windows::Forms::ListView());
			this->columnkeyCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnKeyName = (gcnew System::Windows::Forms::ColumnHeader());
			this->addMacro = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// macroList
			// 
			this->macroList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->macroList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->columnkeyCode, this->columnKeyName });
			this->macroList->HideSelection = false;
			this->macroList->Location = System::Drawing::Point(12, 12);
			this->macroList->Name = L"macroList";
			this->macroList->Size = System::Drawing::Size(567, 224);
			this->macroList->TabIndex = 0;
			this->macroList->UseCompatibleStateImageBehavior = false;
			this->macroList->View = System::Windows::Forms::View::Details;
			this->macroList->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::macroList_MouseDoubleClick);
			// 
			// columnkeyCode
			// 
			this->columnkeyCode->Text = L"Key Code";
			this->columnkeyCode->Width = 130;
			// 
			// columnKeyName
			// 
			this->columnKeyName->Text = L"Name";
			this->columnKeyName->Width = 400;
			// 
			// addMacro
			// 
			this->addMacro->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->addMacro->Location = System::Drawing::Point(12, 253);
			this->addMacro->Name = L"addMacro";
			this->addMacro->Size = System::Drawing::Size(175, 46);
			this->addMacro->TabIndex = 1;
			this->addMacro->Text = L"Add Macro";
			this->addMacro->UseVisualStyleBackColor = true;
			this->addMacro->Click += gcnew System::EventHandler(this, &MainForm::AddMacro_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 28);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(591, 311);
			this->Controls->Add(this->addMacro);
			this->Controls->Add(this->macroList);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(5);
			this->Name = L"MainForm";
			this->Text = L"GameMacro";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	
		private: System::Void AddMacro_Click(System::Object^ sender, System::EventArgs^ e)
		{
			MacroKeyForm^ userDlg = gcnew MacroKeyForm;
			System::Windows::Forms::DialogResult ret = userDlg->ShowDialog();
			if (ret == System::Windows::Forms::DialogResult::OK)
			{
				Redraw();
			}
		}

		private: void Redraw()
		{
			macroList->Items->Clear();

			std::vector<KeySettings::KeyInList> keys;
			if (globalSettings.GetMacroKeyList(keys))
			{
				for (auto key : keys)
				{
					ListViewItem^ lvi = gcnew ListViewItem(ConvertToManagedString(key.keyCodeStr));
					lvi->Tag = key.keyCode;
					lvi->SubItems->Add(ConvertToManagedString(key.name.c_str()));
					macroList->Items->Add(lvi);
				}
			}
		}

		private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) 
		{
			macroList->FullRowSelect = true;
			macroList->GridLines = true;
			Redraw();
		}
		
		private: System::Void macroList_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
		{
			if (macroList->SelectedItems->Count == 1)
			{
				auto item = macroList->SelectedItems[0];

				MacroKeyForm^ userDlg = gcnew MacroKeyForm;
				userDlg->m_keyCode = (uint8_t) item->Tag;
				System::Windows::Forms::DialogResult ret = userDlg->ShowDialog();
				if (ret == System::Windows::Forms::DialogResult::OK)
				{
					Redraw();
				}
			}
		}
	};
}
