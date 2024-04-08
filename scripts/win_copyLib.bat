set arduino_libraries=%USERPROFILE%\Documents\Arduino\libraries
set source_libaries=..\libraries

xcopy %source_libaries% %arduino_libraries% /E /I /Y
pause