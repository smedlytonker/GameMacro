#pragma once

#include "PlaybackKeyForm.h"

namespace GameMacro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MacroKeyForm
	/// </summary>
	public ref class MacroKeyForm : public System::Windows::Forms::Form
	{
	public:
		MacroKeyForm(void)
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
		~MacroKeyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^ macroKeyList;
	protected:

	protected:

	private: System::Windows::Forms::ListView^ playbackKeyList;
	private: System::Windows::Forms::ColumnHeader^ columnkeyCode;
	private: System::Windows::Forms::ColumnHeader^ columnKeyName;
	private: System::Windows::Forms::ColumnHeader^ columnDelay;
	private: System::Windows::Forms::Button^ deleteMacro;
	private: System::Windows::Forms::Button^ addPlaybackKey;
	private: System::Windows::Forms::CheckBox^ checkBoxLoop;
	private: System::Windows::Forms::GroupBox^ groupBoxPlaybackKeys;

	private: System::Windows::Forms::ErrorProvider^ errorProviderMacro;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->macroKeyList = (gcnew System::Windows::Forms::ComboBox());
			this->playbackKeyList = (gcnew System::Windows::Forms::ListView());
			this->columnkeyCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnKeyName = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnDelay = (gcnew System::Windows::Forms::ColumnHeader());
			this->deleteMacro = (gcnew System::Windows::Forms::Button());
			this->addPlaybackKey = (gcnew System::Windows::Forms::Button());
			this->checkBoxLoop = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxPlaybackKeys = (gcnew System::Windows::Forms::GroupBox());
			this->errorProviderMacro = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->groupBoxPlaybackKeys->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProviderMacro))->BeginInit();
			this->SuspendLayout();
			// 
			// macroKeyList
			// 
			this->macroKeyList->Font = (gcnew System::Drawing::Font(L"Verdana", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->macroKeyList->FormattingEnabled = true;
			this->macroKeyList->Location = System::Drawing::Point(13, 22);
			this->macroKeyList->Name = L"macroKeyList";
			this->macroKeyList->Size = System::Drawing::Size(372, 40);
			this->macroKeyList->TabIndex = 0;
			this->macroKeyList->SelectionChangeCommitted += gcnew System::EventHandler(this, &MacroKeyForm::macroKeyList_SelectionChangeCommitted);
			// 
			// playbackKeyList
			// 
			this->playbackKeyList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->playbackKeyList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnkeyCode,
					this->columnKeyName, this->columnDelay
			});
			this->playbackKeyList->HideSelection = false;
			this->playbackKeyList->Location = System::Drawing::Point(31, 52);
			this->playbackKeyList->Name = L"playbackKeyList";
			this->playbackKeyList->Size = System::Drawing::Size(673, 277);
			this->playbackKeyList->TabIndex = 1;
			this->playbackKeyList->UseCompatibleStateImageBehavior = false;
			this->playbackKeyList->View = System::Windows::Forms::View::Details;
			this->playbackKeyList->DoubleClick += gcnew System::EventHandler(this, &MacroKeyForm::playbackKeyList_DoubleClick);
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
			// columnDelay
			// 
			this->columnDelay->Text = L"Delay";
			this->columnDelay->Width = 100;
			// 
			// deleteMacro
			// 
			this->deleteMacro->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->deleteMacro->Location = System::Drawing::Point(579, 22);
			this->deleteMacro->Name = L"deleteMacro";
			this->deleteMacro->Size = System::Drawing::Size(167, 53);
			this->deleteMacro->TabIndex = 2;
			this->deleteMacro->Text = L"Delete";
			this->deleteMacro->UseVisualStyleBackColor = true;
			this->deleteMacro->Click += gcnew System::EventHandler(this, &MacroKeyForm::deleteMacro_Click);
			// 
			// addPlaybackKey
			// 
			this->addPlaybackKey->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->addPlaybackKey->Location = System::Drawing::Point(31, 346);
			this->addPlaybackKey->Name = L"addPlaybackKey";
			this->addPlaybackKey->Size = System::Drawing::Size(288, 53);
			this->addPlaybackKey->TabIndex = 3;
			this->addPlaybackKey->Text = L"Add Playback Key";
			this->addPlaybackKey->UseVisualStyleBackColor = true;
			this->addPlaybackKey->Click += gcnew System::EventHandler(this, &MacroKeyForm::addPlaybackKey_Click);
			// 
			// checkBoxLoop
			// 
			this->checkBoxLoop->AutoSize = true;
			this->checkBoxLoop->Location = System::Drawing::Point(434, 28);
			this->checkBoxLoop->Name = L"checkBoxLoop";
			this->checkBoxLoop->Size = System::Drawing::Size(93, 33);
			this->checkBoxLoop->TabIndex = 4;
			this->checkBoxLoop->Text = L"Loop";
			this->checkBoxLoop->UseVisualStyleBackColor = true;
			this->checkBoxLoop->Click += gcnew System::EventHandler(this, &MacroKeyForm::checkBoxLoop_Click);
			// 
			// groupBoxPlaybackKeys
			// 
			this->groupBoxPlaybackKeys->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBoxPlaybackKeys->Controls->Add(this->playbackKeyList);
			this->groupBoxPlaybackKeys->Controls->Add(this->addPlaybackKey);
			this->groupBoxPlaybackKeys->Location = System::Drawing::Point(13, 99);
			this->groupBoxPlaybackKeys->Name = L"groupBoxPlaybackKeys";
			this->groupBoxPlaybackKeys->Size = System::Drawing::Size(733, 414);
			this->groupBoxPlaybackKeys->TabIndex = 5;
			this->groupBoxPlaybackKeys->TabStop = false;
			this->groupBoxPlaybackKeys->Text = L"Playback Keys";
			// 
			// errorProviderMacro
			// 
			this->errorProviderMacro->ContainerControl = this;
			// 
			// MacroKeyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 28);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(758, 525);
			this->Controls->Add(this->checkBoxLoop);
			this->Controls->Add(this->deleteMacro);
			this->Controls->Add(this->macroKeyList);
			this->Controls->Add(this->groupBoxPlaybackKeys);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(5);
			this->Name = L"MacroKeyForm";
			this->Text = L"Macro";
			this->Load += gcnew System::EventHandler(this, &MacroKeyForm::MacroKeyForm_Load);
			this->groupBoxPlaybackKeys->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProviderMacro))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		public: uint8_t m_keyCode = 0;

		private: void DisplayPlaybackKey(uint8_t macroKeyCode, int playbackIdx)
		{
			if (playbackKeyList->Items->Count > 0)
			{
				PlaybackKeyForm^ userDlg = gcnew PlaybackKeyForm;
				userDlg->m_macroKeyCode = macroKeyCode;
				userDlg->m_playbackIdx = playbackIdx;
				System::Windows::Forms::DialogResult ret = userDlg->ShowDialog();
				if (ret == System::Windows::Forms::DialogResult::OK)
				{
					Redraw();
				}
			}
		}

		private: System::Void addPlaybackKey_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if ((macroKeyList->SelectedIndex < 0) || (m_keyCode == 0))
			{
				errorProviderMacro->SetError(macroKeyList, "No macro key selected");
				macroKeyList->Focus();
				return;
			}

			PlaybackKeyForm^ userDlg = gcnew PlaybackKeyForm;
			userDlg->m_macroKeyCode = m_keyCode;
			userDlg->m_playbackIdx = -1;
			System::Windows::Forms::DialogResult ret = userDlg->ShowDialog();
			if (ret == System::Windows::Forms::DialogResult::OK)
			{
				Redraw();
			}
		}

		private: System::Void deleteMacro_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if ((macroKeyList->SelectedIndex < 0) || (m_keyCode == 0))
			{
				DialogResult = System::Windows::Forms::DialogResult::OK;
				Close();
			}
			else if (globalSettings.Macro_Delete(m_keyCode))
			{
				DialogResult = System::Windows::Forms::DialogResult::OK;
				Close();
			}
		}

		private: void Redraw()
		{
			if (m_keyCode == 0)
			{
				std::vector<KeySettings::KeyEntry> macroKeys;
				if (globalSettings.Macro_ListAvailable(macroKeys, m_keyCode))
				{
					macroKeyList->Items->Clear();
					for (auto key : macroKeys)
					{
						KeyItem^ item = gcnew KeyItem();
						item->keyCode = key.keyCode;
						item->name = ConvertToManagedString(key.name);
						int iPos = macroKeyList->Items->Add(item);
					}
				}
			}
			else
			{
				KeySettings::MacroKey macroKey;
				if (globalSettings.Macro_Get(m_keyCode, macroKey))
				{
					checkBoxLoop->Checked = macroKey.bLoop;

					std::vector<KeySettings::KeyEntry> macroKeys;
					if (globalSettings.Macro_ListAvailable(macroKeys, m_keyCode))
					{
						macroKeyList->Items->Clear();
						for (auto key : macroKeys)
						{
							KeyItem^ item = gcnew KeyItem();
							item->keyCode = key.keyCode;
							item->name = ConvertToManagedString(key.name);
							int iPos = macroKeyList->Items->Add(item);
							if (macroKey.keyCode == key.keyCode)
							{
								macroKeyList->SelectedIndex = iPos;
							}
						}

						playbackKeyList->Items->Clear();
						int playbackIdx = 0;
						for (auto playbackKey : macroKey.keys)
						{
							ListViewItem^ lvi = gcnew ListViewItem(ConvertToManagedString(playbackKey.keyCodeStr));
							lvi->Tag = playbackIdx;
							lvi->SubItems->Add(ConvertToManagedString(playbackKey.name));
							lvi->SubItems->Add(ConvertToManagedString(playbackKey.delayInMSStr));

							playbackKeyList->Items->Add(lvi);
							playbackIdx++;
						}
					}
				}
			}
		}

		private: System::Void MacroKeyForm_Load(System::Object^ sender, System::EventArgs^ e) 
		{
			playbackKeyList->FullRowSelect = true;
			playbackKeyList->GridLines = true;
			Redraw();
		}
		
		private: System::Void playbackKeyList_DoubleClick(System::Object^ sender, System::EventArgs^ e) 
		{
			if(m_keyCode > 0) // Macro key must already be assigned
			{
				if (playbackKeyList->SelectedItems->Count == 1)
				{
					auto item = playbackKeyList->SelectedItems[0];
					DisplayPlaybackKey(m_keyCode, (int) item->Tag);
				}
			}
		}

		private: System::Void macroKeyList_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) 
		{
			if (macroKeyList->SelectedIndex >= 0)
			{
				errorProviderMacro->SetError(macroKeyList, ""); // Clear any errors
			}
			else
			{
				// This should never happen
				errorProviderMacro->SetError(macroKeyList, "No macro key selected");
				macroKeyList->Focus();
				return;
			}

			KeyItem^ item = (KeyItem^) macroKeyList->SelectedItem;
			if (m_keyCode != item->keyCode)
			{
				KeySettings::MacroKey macroKey(item->keyCode);
				if (globalSettings.Macro_Get(m_keyCode, macroKey))
				{
					// Get settings from old macro before we delete it
					// that way we have all the playback keys. The
					// playback keys will move to the new macro key
				}

				if (m_keyCode > 0)
				{
					// Delete old macro from settings file
					globalSettings.Macro_Delete(m_keyCode);
				}

				// Add new macro
				m_keyCode = item->keyCode;
				macroKey.bLoop = checkBoxLoop->Checked;
				globalSettings.Macro_Add(macroKey);
			}
		}

		private: System::Void checkBoxLoop_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if ((macroKeyList->SelectedIndex >= 0) || (m_keyCode > 0))
			{
				KeySettings::MacroKey macroKey;
				if (!globalSettings.Macro_Get(m_keyCode, macroKey))
				{
					// This should not happen
					errorProviderMacro->SetError(macroKeyList, "Macro entry does not exist???");
					macroKeyList->Focus();
					return;
				}
				else
				{
					macroKey.bLoop = checkBoxLoop->Checked;
					globalSettings.Macro_Add(macroKey);
				}
			}
		}
	};
}
