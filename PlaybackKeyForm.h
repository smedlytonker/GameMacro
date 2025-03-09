#pragma once

#include "Common.h"

namespace GameMacro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PlaybackKeyForm
	/// </summary>
	public ref class PlaybackKeyForm : public System::Windows::Forms::Form
	{
	public:
		PlaybackKeyForm(void)
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
		~PlaybackKeyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^ playbackKeyList;
	protected:

	protected:

	private: System::Windows::Forms::Button^ deleteButton;
	private: System::Windows::Forms::TextBox^ textBoxDelay;
	private: System::Windows::Forms::Label^ labelDelay;
	private: System::Windows::Forms::CheckBox^ checkBoxCtrl;
	private: System::Windows::Forms::CheckBox^ checkAlt;
	private: System::Windows::Forms::CheckBox^ checkBoxShift;
	private: System::Windows::Forms::CheckBox^ checkBoxWindows;
	private: System::Windows::Forms::Button^ addUpdateButton;
	private: System::Windows::Forms::ErrorProvider^ errorProviderDelay;
	private: System::Windows::Forms::ErrorProvider^ errorProviderKey;

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
			this->playbackKeyList = (gcnew System::Windows::Forms::ComboBox());
			this->deleteButton = (gcnew System::Windows::Forms::Button());
			this->textBoxDelay = (gcnew System::Windows::Forms::TextBox());
			this->labelDelay = (gcnew System::Windows::Forms::Label());
			this->checkBoxCtrl = (gcnew System::Windows::Forms::CheckBox());
			this->checkAlt = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxShift = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxWindows = (gcnew System::Windows::Forms::CheckBox());
			this->addUpdateButton = (gcnew System::Windows::Forms::Button());
			this->errorProviderDelay = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->errorProviderKey = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProviderDelay))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProviderKey))->BeginInit();
			this->SuspendLayout();
			// 
			// playbackKeyList
			// 
			this->playbackKeyList->Font = (gcnew System::Drawing::Font(L"Verdana", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->playbackKeyList->FormattingEnabled = true;
			this->playbackKeyList->Location = System::Drawing::Point(17, 16);
			this->playbackKeyList->Name = L"playbackKeyList";
			this->playbackKeyList->Size = System::Drawing::Size(472, 40);
			this->playbackKeyList->TabIndex = 1;
			this->playbackKeyList->SelectionChangeCommitted += gcnew System::EventHandler(this, &PlaybackKeyForm::playbackKeyList_SelectionChangeCommitted);
			// 
			// deleteButton
			// 
			this->deleteButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->deleteButton->Location = System::Drawing::Point(448, 275);
			this->deleteButton->Name = L"deleteButton";
			this->deleteButton->Size = System::Drawing::Size(184, 51);
			this->deleteButton->TabIndex = 3;
			this->deleteButton->Text = L"Delete";
			this->deleteButton->UseVisualStyleBackColor = true;
			this->deleteButton->Click += gcnew System::EventHandler(this, &PlaybackKeyForm::deleteButton_Click);
			// 
			// textBoxDelay
			// 
			this->textBoxDelay->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->textBoxDelay->Location = System::Drawing::Point(176, 167);
			this->textBoxDelay->Name = L"textBoxDelay";
			this->textBoxDelay->Size = System::Drawing::Size(157, 35);
			this->textBoxDelay->TabIndex = 4;
			this->textBoxDelay->TextChanged += gcnew System::EventHandler(this, &PlaybackKeyForm::textBoxDelay_TextChanged);
			// 
			// labelDelay
			// 
			this->labelDelay->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelDelay->AutoSize = true;
			this->labelDelay->Location = System::Drawing::Point(17, 167);
			this->labelDelay->Name = L"labelDelay";
			this->labelDelay->Size = System::Drawing::Size(153, 29);
			this->labelDelay->TabIndex = 5;
			this->labelDelay->Text = L"Delay in ms";
			// 
			// checkBoxCtrl
			// 
			this->checkBoxCtrl->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->checkBoxCtrl->AutoSize = true;
			this->checkBoxCtrl->Location = System::Drawing::Point(17, 92);
			this->checkBoxCtrl->Name = L"checkBoxCtrl";
			this->checkBoxCtrl->Size = System::Drawing::Size(122, 33);
			this->checkBoxCtrl->TabIndex = 6;
			this->checkBoxCtrl->Text = L"Control";
			this->checkBoxCtrl->UseVisualStyleBackColor = true;
			// 
			// checkAlt
			// 
			this->checkAlt->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->checkAlt->AutoSize = true;
			this->checkAlt->Location = System::Drawing::Point(185, 92);
			this->checkAlt->Name = L"checkAlt";
			this->checkAlt->Size = System::Drawing::Size(66, 33);
			this->checkAlt->TabIndex = 7;
			this->checkAlt->Text = L"Alt";
			this->checkAlt->UseVisualStyleBackColor = true;
			// 
			// checkBoxShift
			// 
			this->checkBoxShift->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->checkBoxShift->AutoSize = true;
			this->checkBoxShift->Location = System::Drawing::Point(297, 92);
			this->checkBoxShift->Name = L"checkBoxShift";
			this->checkBoxShift->Size = System::Drawing::Size(89, 33);
			this->checkBoxShift->TabIndex = 8;
			this->checkBoxShift->Text = L"Shift";
			this->checkBoxShift->UseVisualStyleBackColor = true;
			// 
			// checkBoxWindows
			// 
			this->checkBoxWindows->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->checkBoxWindows->AutoSize = true;
			this->checkBoxWindows->Location = System::Drawing::Point(432, 92);
			this->checkBoxWindows->Name = L"checkBoxWindows";
			this->checkBoxWindows->Size = System::Drawing::Size(195, 33);
			this->checkBoxWindows->TabIndex = 9;
			this->checkBoxWindows->Text = L"Windows Key";
			this->checkBoxWindows->UseVisualStyleBackColor = true;
			// 
			// addUpdateButton
			// 
			this->addUpdateButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->addUpdateButton->Location = System::Drawing::Point(17, 275);
			this->addUpdateButton->Name = L"addUpdateButton";
			this->addUpdateButton->Size = System::Drawing::Size(209, 51);
			this->addUpdateButton->TabIndex = 10;
			this->addUpdateButton->Text = L"Add/Update";
			this->addUpdateButton->UseVisualStyleBackColor = true;
			this->addUpdateButton->Click += gcnew System::EventHandler(this, &PlaybackKeyForm::addUpdateButton_Click);
			// 
			// errorProviderDelay
			// 
			this->errorProviderDelay->ContainerControl = this;
			// 
			// errorProviderKey
			// 
			this->errorProviderKey->ContainerControl = this;
			// 
			// PlaybackKeyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 28);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(649, 338);
			this->Controls->Add(this->addUpdateButton);
			this->Controls->Add(this->checkBoxWindows);
			this->Controls->Add(this->checkBoxShift);
			this->Controls->Add(this->checkAlt);
			this->Controls->Add(this->checkBoxCtrl);
			this->Controls->Add(this->labelDelay);
			this->Controls->Add(this->textBoxDelay);
			this->Controls->Add(this->deleteButton);
			this->Controls->Add(this->playbackKeyList);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(5);
			this->Name = L"PlaybackKeyForm";
			this->Text = L"Playback Key";
			this->Load += gcnew System::EventHandler(this, &PlaybackKeyForm::PlaybackKeyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProviderDelay))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProviderKey))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		public: uint8_t m_macroKeyCode = 0;
		public: int m_playbackIdx = -1;

		private: System::Void addUpdateButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (playbackKeyList->SelectedIndex < 0)
			{
				errorProviderKey->SetError(playbackKeyList, "No key selected");
				playbackKeyList->Focus();
				return;
			}

			KeyItem^ item = (KeyItem^) playbackKeyList->SelectedItem;
			KeySettings::PlaybackKey playbackKey;

			if (item->keyCode == 0)
			{
				errorProviderKey->SetError(playbackKeyList, "No key selected");
				playbackKeyList->Focus();
				return;
			}

			playbackKey.delayInMSStr = ConvertToUnmanagedString(textBoxDelay->Text);
			if (playbackKey.delayInMSStr.empty())
			{
				errorProviderDelay->SetError(textBoxDelay, "Invalid delay value");
				textBoxDelay->Focus();
				return;
			}

			playbackKey.delayInMSStr = std::regex_replace(playbackKey.delayInMSStr, std::regex("[^0-9]"), "");
			if (playbackKey.delayInMSStr.empty())
			{
				errorProviderDelay->SetError(textBoxDelay, "Invalid delay value");
				textBoxDelay->Focus();
				return;
			}

			playbackKey.delayInMS = (uint16_t)std::stoi(playbackKey.delayInMSStr);
			if ((playbackKey.delayInMS == 0) || (playbackKey.delayInMS > 30000))
			{
				errorProviderDelay->SetError(textBoxDelay, "Invalid delay value");
				textBoxDelay->Focus();
				return;
			}

			if (m_playbackIdx > 0)
			{
				if (globalSettings.Playback_Get(m_macroKeyCode, m_playbackIdx, playbackKey))
				{
					// Gets the orginal key
				}
				else
				{
					// This should not happen
					// If it does treat it as new key
					m_playbackIdx = -1;
				}
			}

			playbackKey.keyCode = item->keyCode;
			playbackKey.bCtrl   = checkBoxCtrl->Checked;
			playbackKey.bAlt    = checkAlt->Checked;
			playbackKey.bShift  = checkBoxShift->Checked;
			playbackKey.bWKey   = checkBoxWindows->Checked;
			
			if (globalSettings.Playback_Add(m_macroKeyCode, m_playbackIdx, playbackKey))
			{
				DialogResult = System::Windows::Forms::DialogResult::OK;
				Close();
			}
		}
	
		private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (m_playbackIdx < 0)
			{
				// Nothing to delete
				DialogResult = System::Windows::Forms::DialogResult::Cancel;
				Close();
			}
			else
			{
				if (globalSettings.Playback_Delete(m_macroKeyCode, m_playbackIdx))
				{
					DialogResult = System::Windows::Forms::DialogResult::OK;
					Close();
				}
			}
		}

		private: System::Void playbackKeyList_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e)
		{
			errorProviderKey->SetError(playbackKeyList, "");
		}

		private: System::Void textBoxDelay_TextChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			std::string delayStr = ConvertToUnmanagedString(textBoxDelay->Text);

			// Remove all non-numeric characters
			std::string nonNumericCharactersRemoved = std::regex_replace(delayStr, std::regex("[^0-9]"), "");
			if (delayStr != nonNumericCharactersRemoved)
			{
				textBoxDelay->Text = ConvertToManagedString(nonNumericCharactersRemoved);
			}

			if(String::IsNullOrWhiteSpace(textBoxDelay->Text))
				errorProviderDelay->SetError(textBoxDelay, "");
		}

		private: void Redraw(int playbackIdx)
		{
			if (m_macroKeyCode > 0)
			{
				uint8_t keyCodeOfPlaybackKey = 0;

				if (playbackIdx >= 0)
				{
					KeySettings::PlaybackKey playbackKey;
					if (globalSettings.Playback_Get(m_macroKeyCode, playbackIdx, playbackKey))
					{
						keyCodeOfPlaybackKey = playbackKey.keyCode;
						checkBoxCtrl->Checked = playbackKey.bCtrl;
						checkAlt->Checked = playbackKey.bAlt;
						checkBoxShift->Checked = playbackKey.bShift;
						checkBoxWindows->Checked = playbackKey.bWKey;
						textBoxDelay->Text = ConvertToManagedString(playbackKey.delayInMSStr);
					}
				}

				std::vector<KeySettings::KeyEntry> keys;
				if (globalSettings.Playback_ListAvailable(keys))
				{
					playbackKeyList->Items->Clear();

					for (auto key : keys)
					{
						KeyItem^ item = gcnew KeyItem();
						item->keyCode = key.keyCode;
						item->name = ConvertToManagedString(key.name);
						int iPos = playbackKeyList->Items->Add(item);

						if (keyCodeOfPlaybackKey == key.keyCode)
						{
							playbackKeyList->SelectedIndex = iPos;
						}
					}
				}
			}
		}

		private: System::Void PlaybackKeyForm_Load(System::Object^ sender, System::EventArgs^ e) 
		{
			Redraw(m_playbackIdx);
		}
		
	};
}
