#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    semprojectdsa::MyForm form;
    Application::Run(% form);
    return 0;
}
