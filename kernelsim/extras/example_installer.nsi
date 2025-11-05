
Name "KernelSim"
OutFile "kernelsim_installer.exe"
InstallDir "$PROGRAMFILES\KernelSim"
Page directory
Page instfiles

Section "Install"
  SetOutPath "$INSTDIR"
  File "kernelsim.exe"
  CreateShortCut "$DESKTOP\KernelSim.lnk" "$INSTDIR\kernelsim.exe"
SectionEnd
