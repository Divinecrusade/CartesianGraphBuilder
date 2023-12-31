#pragma once

#include "Validater.hpp"
#include "CartesianSystem.hpp"

namespace GUIApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ graphArea;
	protected:
	private: System::Windows::Forms::GroupBox^ inputGroup;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ buildPlot;
	private: System::Windows::Forms::ErrorProvider^ errorFormula;
	private: System::Windows::Forms::TrackBar^ systemScale;
	private: System::Windows::Forms::Label^ label3;


	private: System::Windows::Forms::TextBox^ formula;

	private: void MarshalString(String^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->graphArea = (gcnew System::Windows::Forms::Panel());
			this->inputGroup = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->systemScale = (gcnew System::Windows::Forms::TrackBar());
			this->buildPlot = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->formula = (gcnew System::Windows::Forms::TextBox());
			this->errorFormula = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->inputGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->systemScale))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorFormula))->BeginInit();
			this->SuspendLayout();
			// 
			// graphArea
			// 
			this->graphArea->BackColor = System::Drawing::SystemColors::Window;
			this->graphArea->Location = System::Drawing::Point(33, 33);
			this->graphArea->Margin = System::Windows::Forms::Padding(0, 0, 10, 0);
			this->graphArea->Name = L"graphArea";
			this->graphArea->Size = System::Drawing::Size(700, 700);
			this->graphArea->TabIndex = 0;
			this->graphArea->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::graphArea_Paint);
			// 
			// inputGroup
			// 
			this->inputGroup->BackColor = System::Drawing::SystemColors::Control;
			this->inputGroup->Controls->Add(this->label3);
			this->inputGroup->Controls->Add(this->systemScale);
			this->inputGroup->Controls->Add(this->buildPlot);
			this->inputGroup->Controls->Add(this->label2);
			this->inputGroup->Controls->Add(this->label1);
			this->inputGroup->Controls->Add(this->formula);
			this->inputGroup->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->inputGroup->Location = System::Drawing::Point(746, 33);
			this->inputGroup->Name = L"inputGroup";
			this->inputGroup->Size = System::Drawing::Size(405, 700);
			this->inputGroup->TabIndex = 1;
			this->inputGroup->TabStop = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 196);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(175, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"������� ������������ �������";
			// 
			// systemScale
			// 
			this->systemScale->Location = System::Drawing::Point(11, 212);
			this->systemScale->Maximum = 9;
			this->systemScale->Minimum = 1;
			this->systemScale->Name = L"systemScale";
			this->systemScale->Size = System::Drawing::Size(368, 45);
			this->systemScale->TabIndex = 4;
			this->systemScale->Value = 1;
			this->systemScale->ValueChanged += gcnew System::EventHandler(this, &MainForm::systemScale_ValueChanged);
			// 
			// buildPlot
			// 
			this->buildPlot->Location = System::Drawing::Point(304, 77);
			this->buildPlot->Name = L"buildPlot";
			this->buildPlot->Size = System::Drawing::Size(75, 23);
			this->buildPlot->TabIndex = 3;
			this->buildPlot->Text = L"���������";
			this->buildPlot->UseVisualStyleBackColor = true;
			this->buildPlot->Click += gcnew System::EventHandler(this, &MainForm::buildPlot_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 53);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(21, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"y =";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(105, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"������� ���������";
			// 
			// formula
			// 
			this->formula->Location = System::Drawing::Point(35, 50);
			this->formula->Name = L"formula";
			this->formula->Size = System::Drawing::Size(345, 20);
			this->formula->TabIndex = 0;
			this->formula->TextChanged += gcnew System::EventHandler(this, &MainForm::formula_TextChanged);
			this->formula->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::formula_KeyPress);
			// 
			// errorFormula
			// 
			this->errorFormula->ContainerControl = this;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Desktop;
			this->ClientSize = System::Drawing::Size(1184, 761);
			this->Controls->Add(this->inputGroup);
			this->Controls->Add(this->graphArea);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximumSize = System::Drawing::Size(1200, 800);
			this->MinimumSize = System::Drawing::Size(1200, 800);
			this->Name = L"MainForm";
			this->Padding = System::Windows::Forms::Padding(30);
			this->Text = L"CGB";
			this->inputGroup->ResumeLayout(false);
			this->inputGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->systemScale))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorFormula))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void formula_KeyPress(System::Object^, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (!Validater::validate(e->KeyChar))
	{
		e->Handled = true;
	}
}
private: System::Void buildPlot_Click(System::Object^, System::EventArgs^) {
	if (errorFormula->GetError(formula)->Length != 0) return;

	String^ system_str_expr{ formula->Text };
	std::string std_str_expr{ };

	MarshalString(system_str_expr, std_str_expr);

	CartesianSystem::Plot::set(std_str_expr);
	graphArea->Invalidate();
}
private: System::Void formula_TextChanged(System::Object^, System::EventArgs^) {
	String^ system_str_expr{ formula->Text };
	std::string std_str_expr{ };
	
	MarshalString(system_str_expr, std_str_expr);

	if (!Validater::validate(std_str_expr))
	{
		errorFormula->SetError(formula, "Error in formula");
		buildPlot->Enabled = false;
	}
	else
	{
		errorFormula->SetError(formula, "");
		buildPlot->Enabled = true;
	}
}
private: System::Void graphArea_Paint(System::Object^, System::Windows::Forms::PaintEventArgs^ e) {
	CartesianSystem::set(graphArea->Size, systemScale->Value);
	CartesianSystem::draw(e->Graphics);
	CartesianSystem::Plot::draw(e->Graphics);
}
private: System::Void systemScale_ValueChanged(System::Object^, System::EventArgs^) {
	graphArea->Invalidate();
}
};
}
