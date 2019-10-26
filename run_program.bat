@echo off

if exist C:\MinGW\ (
    echo MinGW: OK

    if exist C:\MinGW\freeglut\ (
        echo "freeglut directory: OK"
        goto:build
    ) else (
        setlocal
        :message
        set /p decision="���带 ���� freeglut ���̺귯���� ��ġ�Ͻðڽ��ϱ�(y/n)?: "
        if /i [%decision%]==[n] (
            endlocal
            GOTO:end
        ) else (
            if /i [%decision%]==[y] (
                endlocal
                GOTO:insfreeglut
            ) else (
                GOTO:message
            )
        )
    
        

        :insfreeglut
        echo "freeglut directory: create new directory"
        mkdir C:\MinGW\freeglut\

        echo "Copying freeglut libs into C:\MinGW\freeglut\"
        xcopy freeglut C:\MinGW\freeglut /s /h /e /d /y

        echo "freeglut ��ġ �Ϸ�"

        goto:build
    )

) else (
    echo "C:\MinGW\ �� MinGW�� ��ġ�Ǿ� �ִ��� Ȯ�� �� �������ּ���."
    GOTO:end
)

:build



if not exist %cd%\build (
    mkdir %cd%\build
)

@echo on
configure_temp.js && buildscript2.bat
@echo off

rmdir %cd%\build /s /q

del %cd%\buildscript2.bat /Q

:end
PAUSE