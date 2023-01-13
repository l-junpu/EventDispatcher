@echo OFF

@REM [92m is Green, [93m is Yellow, [96m is Cyan, [97m is White (color for echo)
set RootPath=%cd%
set CMakeBuildFolder="%RootPath%\build"

@REM Cloning from git
call :clone_git xxHash https://github.com/RedSpah/xxhash_cpp


echo [96m==============================================================================
echo   Done
echo ==============================================================================[97m
pause











@REM ===================================================================================
@REM							    	Helper Functions
@REM ===================================================================================

@REM Cloning from git url
@REM %1 is the lib, %2 is the git url
:clone_git
echo [96m==============================================================================
echo   Cloning %1 from main/master branch
echo ==============================================================================[97m
REM Remove the dir if it already exist
call :rmdir_if_exist "Dependencies/%1"
echo Starting to clone...
git clone %2 "Dependencies/%1"
echo.
EXIT /B 0

@REM Cloning from git url with stated branch
@REM %1 is the lib, %2 is the git url, %3 is the branch
:clone_git_branch
echo [96m==============================================================================
echo   Cloning %1 from %3 branch
echo ==============================================================================[97m
REM Remove the dir if it already exist
call :rmdir_if_exist "Dependencies/%1"
echo Starting to clone...
git clone --branch "%3" %2 "Dependencies/%1"
echo.
EXIT /B 0