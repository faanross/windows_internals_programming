#include <Windows.h>
#include <stdio.h>

int main()
{
	WCHAR name[] = L"notepad";
	STARTUPINFO si = { sizeof(si) }; // adds sizeof cb as first member, 0s out the rest
	PROCESS_INFORMATION pi; // since it's an output structure nothing we need to add 

	BOOL success = CreateProcessW(nullptr, name, nullptr, nullptr, FALSE, HIGH_PRIORITY_CLASS, nullptr, nullptr, &si, &pi);
	if (success) {
		printf("PID: %u, TID: %u\n", pi.dwProcessId, pi.dwThreadId);

		if (WAIT_TIMEOUT == WaitForSingleObject(pi.hProcess, 10000)) {
			printf("notepad still executing code...\n");
		}
		else
		{
			DWORD code;
			GetExitCodeProcess(pi.hProcess, &code);
			printf("Notepad has terminated with code: %u\n", code);
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);	
	}
	else {
		printf("could not create process - %u\n", GetLastError()); // remember LastError() is stored in TEB
	}
	return 0;
}