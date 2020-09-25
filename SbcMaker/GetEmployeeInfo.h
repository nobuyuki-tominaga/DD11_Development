#ifndef GET_EMPLOYEE_INFO_H
#define GET_EMPLOYEE_INFO_H

#include <curl/curl.h>
#include "SbcMakerCommon.h"

class CEmployeeInfo
{
private:
    QString searchHofficeInfo(QString dept);
    QString setEngPositionInfo(QString position);
public:
    CEmployeeInfo();  // Constructor
    ~CEmployeeInfo(); // Destructor
    int getEmployeeInfo(EMPLOYEE_INFO *info, QString EmployeeNo);  // Main Process
};

#endif  // GET_EMPLOYEE_INFO_H

