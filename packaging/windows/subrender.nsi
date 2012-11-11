#
# Subrender NSIS installer script
#
# This is an altered version of the Subsurface Windows installer
# script.
#
# Authors / Copyright: Dirk Hohndel, Ivan Habunek, Lubomir I. Ivanov
# License: GPL v2
# Original Source: https://github.com/torvalds/subsurface/blob/ffd3b8591dcb4b22dc318b6a39bb4e2ac8140f42/packaging/windows/subsurface.nsi

#--------------------------------
# Include Modern UI

    !include "MUI2.nsh"

#--------------------------------
# General

    # Program version
    !define SUBRENDER_VERSION "0.3.0"

    # VIProductVersion requires version in x.x.x.x format
    !define SUBRENDER_VIPRODUCTVERSION "0.3.0.0"

    # Installer name and filename
    Name "Subrender"
    Caption "Subrender ${SUBRENDER_VERSION} Setup"
    OutFile "subrender-${SUBRENDER_VERSION}.exe"

    # Icon to use for the installer
    !define MUI_ICON "subrender.ico"

    # Default installation folder
    InstallDir "$PROGRAMFILES\Subrender"

    # Get installation folder from registry if available
    InstallDirRegKey HKCU "Software\subrender\subrender" ""

    # Request application privileges
    RequestExecutionLevel admin

#--------------------------------
# Version information

    VIProductVersion "${SUBRENDER_VIPRODUCTVERSION}"
    VIAddVersionKey "ProductName" "Subrender"
    VIAddVersionKey "FileDescription" "Subrender - generate beautiful animations of your dives"
    VIAddVersionKey "FileVersion" "${SUBRENDER_VERSION}"
    VIAddVersionKey "LegalCopyright" "GPL Version 3"
    VIAddVersionKey "ProductVersion" "${SUBRENDER_VERSION}"

#--------------------------------
# Settings

    # Show a warn on aborting installation
    !define MUI_ABORTWARNING

    # Defines the target start menu folder
    !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
    !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Subrender"
    !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"

#--------------------------------
# Variables

    Var StartMenuFolder

#--------------------------------
# Pages

    # Installer pages
    !insertmacro MUI_PAGE_LICENSE "..\..\gpl-3.0.txt"
    !insertmacro MUI_PAGE_DIRECTORY
    !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
    !insertmacro MUI_PAGE_INSTFILES

    # Uninstaller pages
    !insertmacro MUI_UNPAGE_CONFIRM
    !insertmacro MUI_UNPAGE_INSTFILES

#--------------------------------
# Languages

    !insertmacro MUI_LANGUAGE "English"

#--------------------------------
# Default installer section

Section
    SetShellVarContext all

    # Installation path
    SetOutPath "$INSTDIR"

    # Delete any already installed DLLs to avoid buildup of various
    # versions of the same library when upgrading
    Delete "$INSTDIR\*.dll"

    # Files to include in installer
    File subrender.exe
    File libgcc_s_dw2-1.dll
    File mingwm10.dll
    File QtCore4.dll
    File QtGui4.dll
    File QtXml4.dll
    File subrender.ico

    # Store installation folder in registry
    WriteRegStr HKCU "Software\subrender\subrender" "" $INSTDIR

    # Create shortcuts
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
        CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
        CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Subrender.lnk" "$INSTDIR\subrender.exe"
        CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall Subrender.lnk" "$INSTDIR\Uninstall.exe"
    !insertmacro MUI_STARTMENU_WRITE_END

    # Create the uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

#--------------------------------
# Uninstaller section

Section "Uninstall"
    SetShellVarContext all

    # Delete installed files
    Delete "$INSTDIR\*.dll"
    Delete "$INSTDIR\subrender.exe"
    Delete "$INSTDIR\subrender.ico"
    Delete "$INSTDIR\Uninstall.exe"
    RMDir "$INSTDIR"

    # Remove shortcuts
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    Delete "$SMPROGRAMS\$StartMenuFolder\Subrender.lnk"
    Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall Subrender.lnk"
    RMDir "$SMPROGRAMS\$StartMenuFolder"

    # Remove registry entries
    DeleteRegKey /ifempty HKCU "Software\subrender"

SectionEnd
