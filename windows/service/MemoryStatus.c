#include <windows.h>
#include <stdio.h>

#define sleepTime 5000
#define logFile "E:\\Study\\CPP\\service\\service.log"

//SC CREATE MemoryStatus binpath= "E:\Study\CPP\service\MemoryStatus.exe"
//SC DELETE MemoryStatus

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE serviceStatusHandle;

int writeToLog(char *str);
int initService();
void serviceControlHandler(DWORD request);
void serviceMain();

int main(int argc, char **argv) {
    SERVICE_TABLE_ENTRY entry[2];
    entry[0].lpServiceName = L"MemoryStatus";
    entry[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)serviceMain;
    entry[1].lpServiceName = NULL;
    entry[1].lpServiceName = NULL;

    StartServiceCtrlDispatcher(entry);
    return 0;
}


void serviceMain() {
    //writeToLog("serviceMain\n");
    serviceStatus.dwServiceType             = SERVICE_WIN32;
    serviceStatus.dwCurrentState            = SERVICE_START_PENDING;
    serviceStatus.dwControlsAccepted        = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    serviceStatus.dwWin32ExitCode           = 0;
    serviceStatus.dwServiceSpecificExitCode = 0;
    serviceStatus.dwCheckPoint              = 0;
    serviceStatus.dwWaitHint                = 0;

    serviceStatusHandle = RegisterServiceCtrlHandler(
        L"MemoryStatus",
        (LPHANDLER_FUNCTION)serviceControlHandler
    );

    if(serviceStatusHandle == NULL) {
        return;
    }

    int error = initService();
    if(error) {
        serviceStatus.dwCurrentState     = SERVICE_STOPPED;
        serviceStatus.dwWin32ExitCode   = -1;
        SetServiceStatus(serviceStatusHandle, &serviceStatus);
        return ;
    }

    serviceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(serviceStatusHandle, &serviceStatus);

    MEMORYSTATUS memory;

    while(serviceStatus.dwCurrentState == SERVICE_RUNNING) {
        //writeToLog("serviceMainwhile\n");
        char buffer[20];
        GlobalMemoryStatus(&memory);
        sprintf(buffer, "There are free  %8.1I64d Mbytes of physical memory.", memory.dwAvailPhys/1024/1024);
        
        int result = writeToLog(buffer);
        if(result) {
            serviceStatus.dwCurrentState    = SERVICE_STOPPED;
            serviceStatus.dwWin32ExitCode   = -1;
            SetServiceStatus(serviceStatusHandle, &serviceStatus);
            return ;
        }
        Sleep(sleepTime);
    }
    return ;
}

void serviceControlHandler(DWORD request) {
    //writeToLog("serviceControlHandler\n");
    switch (request) {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        writeToLog("Monitoring stopped.");
        serviceStatus.dwWin32ExitCode = 0;
        serviceStatus.dwCurrentState = SERVICE_STOPPED;
        break;
    default:
        break;
    }
    SetServiceStatus(serviceStatusHandle, &serviceStatus);
    return ;
}

int writeToLog(char *str) {
    FILE *log;
    log = fopen(logFile, "a+");
    if(log == NULL) {
        return -1;
    }
    fprintf(log, "%s\n", str);
    fclose(log);
    return 0;
}

int initService() {
    int result;
    result = writeToLog("Monitoring started.");
    return result;
}