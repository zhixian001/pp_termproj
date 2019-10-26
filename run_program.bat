@echo off

if exist C:\MinGW\ (
    echo MinGW: OK

    if exist C:\MinGW\freeglut\ (
        echo "freeglut directory: OK"
        goto:build
    ) else (
        setlocal
        :message
        set /p decision="빌드를 위해 freeglut 라이브러리를 설치하시겠습니까(y/n)?: "
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

        echo "freeglut 설치 완료"

        goto:build
    )

) else (
    echo "C:\MinGW\ 에 MinGW가 설치되어 있는지 확인 후 실행해주세요."
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