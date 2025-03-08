#pragma once

#include "Common.h"
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
	private: System::Windows::Forms::Button^ addUpdate;
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
			this->macroKeyList = (gcnew System::Windows::Forms::ComboBox());
			this->playbackKeyList = (gcnew System::Windows::Forms::ListView());
			this->columnkeyCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnKeyName = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnDelay = (gcnew System::Windows::Forms::ColumnHeader());
			this->deleteMacro = (gcnew System::Windows::Forms::Button());
			this->addPlaybackKey = (gcnew System::Windows::Forms::Button());
			this->checkBoxLoop = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxPlaybackKeys = (gcnew System::Windows::Forms::GroupBox());
			this->addUpdate = (gcnew System::Windows::Forms::Button());
			this->groupBoxPlaybackKeys->SuspendLayout();
			this->SuspendLayout();
			// 
			// macroKeyList
			// 
			this->macroKeyList->Font = (gcnew System::Drawing::Font(L"Verdana", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->macroKeyList->FormattingEnabled = true;
			this->macroKeyList->Location = System::Drawing::Point(13, 15);
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
			this->playbackKeyList->Location = System::Drawing::Point(31, 51);
			this->playbackKeyList->Name = L"playbackKeyList";
			this->playbackKeyList->Size = System::Drawing::Size(694, 219);
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
			this->deleteMacro->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->deleteMacro->Location = System::Drawing::Point(13, 487);
			this->deleteMacro->Name = L"deleteMacro";
			this->deleteMacro->Size = System::Drawing::Size(214, 53);
			this->deleteMacro->TabIndex = 2;
			this->deleteMacro->Text = L"Delete";
			this->deleteMacro->UseVisualStyleBackColor = true;
			this->deleteMacro->Click += gcnew System::EventHandler(this, &MacroKeyForm::deleteMacro_Click);
			// 
			// addPlaybackKey
			// 
			this->addPlaybackKey->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->addPlaybackKey->Location = System::Drawing::Point(31, 291);
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
			this->checkBoxLoop->Location = System::Drawing::Point(448, 22);
			this->checkBoxLoop->Name = L"checkBoxLoop";
			this->checkBoxLoop->Size = System::Drawing::Size(93, 33);
			this->checkBoxLoop->TabIndex = 4;
			this->checkBoxLoop->Text = L"Loop";
			this->checkBoxLoop->UseVisualStyleBackColor = true;
			// 
			// groupBoxPlaybackKeys
			// 
			this->groupBoxPlaybackKeys->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBoxPlaybackKeys->Controls->Add(this->playbackKeyList);
			this->groupBoxPlaybackKeys->Controls->Add(this->addPlaybackKey);
			this->groupBoxPlaybackKeys->Location = System::Drawing::Point(13, 84);
			this->groupBoxPlaybackKeys->Name = L"groupBoxPlaybackKeys";
			this->groupBoxPlaybackKeys->Size = System::Drawing::Size(754, 365);
			this->groupBoxPlaybackKeys->TabIndex = 5;
			this->groupBoxPlaybackKeys->TabStop = false;
			this->groupBoxPlaybackKeys->Text = L"Playback Keys";
			// 
			// addUpdate
			// 
			this->addUpdate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->addUpdate->Location = System::Drawing::Point(545, 487);
			this->addUpdate->Name = L"addUpdate";
			this->addUpdate->Size = System::Drawing::Size(222, 53);
			this->addUpdate->TabIndex = 6;
			this->addUpdate->Text = L"Add / Update";
			this->addUpdate->UseVisualStyleBackColor = true;
			this->addUpdate->Click += gcnew System::EventHandler(this, &MacroKeyForm::addUpdate_Click);
			// 
			// MacroKeyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 28);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(779, 552);
			this->Controls->Add(this->addUpdate);
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
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		public: uint8_t m_keyCode = 0;


		private: void DisplayPlaybackKey(uint8_t macroKeyCode, int playbackKeyVectorIdx)
		{
			if (playbackKeyList->Items->Count > 0)
			{
				PlaybackKeyForm^ userDlg = gcnew PlaybackKeyForm;
				userDlg->m_macroKeyCode = macroKeyCode;
				userDlg->m_playbackKeyVectorIdx = playbackKeyVectorIdx;
				System::Windows::Forms::DialogResult ret = userDlg->ShowDialog();
				if (ret == System::Windows::Forms::DialogResult::OK)
				{
					Redraw();
				}
			}
		}

		private: System::Void addPlaybackKey_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (macroKeyList->SelectedIndex < 0)
			{
				MessageBox::Show("No macro key selected");
				return;
			}

			if (m_keyCode == 0)
			{
				MessageBox::Show("Macro has to be selected first");
				return;
			}

			PlaybackKeyForm^ userDlg = gcnew PlaybackKeyForm;
			userDlg->m_macroKeyCode = m_keyCode;
			userDlg->m_playbackKeyVectorIdx = -1;
			System::Windows::Forms::DialogResult ret = userDlg->ShowDialog();
			if (ret == System::Windows::Forms::DialogResult::OK)
			{
				Redraw();
			}
		}

		private: System::Void deleteMacro_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (macroKeyList->SelectedIndex < 0)
			{
				MessageBox::Show("No macro key selected");
				return;
			}

			if (m_keyCode == 0)
			{
				MessageBox::Show("Macro has to be selected first");
				return;
			}

			if (settings.DeleteMacroKey(m_keyCode))
			{
				DialogResult = System::Windows::Forms::DialogResult::OK;
				Close();
			}
		}

		private: System::Void addUpdate_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (macroKeyList->SelectedIndex < 0)
			{
				MessageBox::Show("No macro key selected");
				return;
			}

			if (m_keyCode == 0)
			{
				MessageBox::Show("Macro has to be selected first");
				return;
			}

			KeySettings::MacroKey macroKey;
			if (!settings.GetMacroKey(m_keyCode, macroKey))
			{
				// This should not happen
				MessageBox::Show("Macro entry does not exist??");
				return;
			}
			else
			{
				macroKey.bLoop = checkBoxLoop->Checked;
				if (settings.AddMacroKey(macroKey))
				{
					DialogResult = System::Windows::Forms::DialogResult::OK;
					Close();
				}
			}
		}

		private: void Redraw()
		{
			if (m_keyCode == 0)
			{
				std::vector<KeySettings::KeyInList> macroKeys;
				if (settings.GetAvialableMacroKeys(macroKeys, m_keyCode))
				{
					macroKeyList->Items->Clear();
					for (auto key : macroKeys)
					{
						MacroItem^ item = gcnew MacroItem();
						item->keyCode = key.keyCode;
						item->name = ConvertToManagedString(key.name);
						int iPos = macroKeyList->Items->Add(item);
					}
				}
			}
			else
			{
				KeySettings::MacroKey macroKey;
				if (settings.GetMacroKey(m_keyCode, macroKey))
				{
					std::vector<KeySettings::KeyInList> macroKeys;
					if (settings.GetAvialableMacroKeys(macroKeys, m_keyCode))
					{
						checkBoxLoop->Checked = macroKey.bLoop;

						macroKeyList->Items->Clear();
						for (auto key : macroKeys)
						{
							MacroItem^ item = gcnew MacroItem();
							item->keyCode = key.keyCode;
							item->name = ConvertToManagedString(key.name);
							int iPos = macroKeyList->Items->Add(item);
							if (macroKey.keyCode == key.keyCode)
							{
								macroKeyList->SelectedIndex = iPos;
							}
						}

						playbackKeyList->Items->Clear();
						int playbackKeyVectorIdx = 0;
						for (auto playbackKey : macroKey.keys)
						{
							ListViewItem^ lvi = gcnew ListViewItem(ConvertToManagedString(playbackKey.keyCodeStr));
							lvi->Tag = playbackKeyVectorIdx;
							lvi->SubItems->Add(ConvertToManagedString(playbackKey.name));
							lvi->SubItems->Add(ConvertToManagedString(playbackKey.delayInMSStr));

							playbackKeyList->Items->Add(lvi);
							playbackKeyVectorIdx++;
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
			if (macroKeyList->SelectedIndex < 0)
			{
				MessageBox::Show("No macro key selected");
				return;
			}

			MacroItem^ item = (MacroItem^)macroKeyList->SelectedItem;
			if (m_keyCode != item->keyCode)
			{
				KeySettings::MacroKey macroKey;
				if (settings.GetMacroKey(m_keyCode, macroKey))
				{
					// Get settings from old macro before we delete it
					// that way we have all the playback keys. The
					// playback keys will move to the new macro key
				}

				if (m_keyCode > 0)
				{
					// Delete old macro
					settings.DeleteMacroKey(m_keyCode);
				}

				// Add new macro
				m_keyCode = item->keyCode;
				macroKey.keyCode = m_keyCode;
				macroKey.bLoop = checkBoxLoop->Checked;
				settings.AddMacroKey(macroKey);
			}
		}

	};
}
