<# quick_clean.ps1 (by matthew pool)
    * calls deep_clean.ps1 (EDITED)

.SYNOPSIS
    * powershell script used to update, clean, and optimize windows

.WARNING:   move .ps1 /.bat files to new pc at "$home\documents\~mp utilities\"
            * run as admin!

.RUN POWERSHELL:    ps c:\ $home\documents\quick_clean.ps1
    
.RUN CMD:   c:\ powershell -File "c:\users\public\desktop\quick_clean.ps1"

.RUN SHORTCUT:
    * create shortcut to file
    * right-click shortcut  >> properties   >> advanced    >> CHECK Run as Administrator
                                            >> options tab >> UNCHECK Quick Edit Mode

#.HELP: Get-Help [command]
#.SEARCH OPTIONS:   CTRL SHIFT P


====================================================================================================================================================================================
#>

# sets error text color to 'Red'
$host.PrivateData.ErrorForegroundColor = 'Red'

# sets default action of handling errors: Continue (default), Stop, Inquire, SilentlyContinue (Ignore, Suspend?)
$ErrorActionPreference = 'SilentlyContinue' #Stop

# CLEAR
clear-host


#LOGFILE
$error_counter = 0

#DELETE LOGFILE
write-output "Searching for old log files to delete..."

# $home = "c:\users\public"
set-location -Path "$home\desktop"

# deletes logfile.log if it already exists
remove-item "$home\desktop\logfile.log" -ErrorAction Ignore


#WRITE_LOG

<#> METHOD 1
# $LOGSTRING >> $LOGFILE
$logstring = "NO ERRORS METHOD 1"
$logfile = "$home\desktop\logfile.log"
$logstring >> $logfile
<#>


<#>METHOD 2
function write_log {

    $logstring = "NO ERRORS METHOD 2"
    param ([string]$logstring)
    Add-Content $logfile -value $logstring
}
write_log
<#>


<#>TRY / CATCH
try {write-output "commands..."}

# if errors occured during try
catch {write-output "caught an error in try section"}

# finally section (optional)
finally {write-output "code that must still run"}
<#>


#DETAILED ERROR-HANDLING
function write_errorlog {
         
    [CmdletBinding()]
    
    param (
    
        [Parameter(Mandatory=$false, HelpMessage = " Error from computer.")]
        [string]$hostname,
        
        [Parameter(Mandatory=$false, HelpMessage = " Environment that failed. (Test, Production, Course, Acceptance...)")] 
        [string]$env,

        [Parameter(Mandatory=$false, HelpMessage= " Type of server that failed. (Application, Web, Integration...)")] 
        [string]$logicalname,
    
        [Parameter(Mandatory=$false, HelpMessage= " Error message.")] 
        [string]$errormsg,
    
        [Parameter( Mandatory=$false, HelpMessage= " Exception.")]
        [string]$exception,
    
        [Parameter(Mandatory=$false, HelpMessage= " Name of the script that is failing.")]
        [string]$scriptname,
     
        [Parameter(Mandatory=$false, HelpMessage= " Script fails at line number.")]
        [string]$failinglinenumber,

        [Parameter(Mandatory=$false, HelpMessage= " Failing line looks like.")]
        [string]$failingline,
    
        [Parameter(Mandatory=$false, HelpMessage= " Powershell command path.")]
        [string]$pscommandpath,    

        [Parameter(Mandatory=$false, HelpMessage= "Position message.")]
        [string]$positionmsg, 

        [Parameter(Mandatory=$false, HelpMessage= "Stack trace.")]
        [string]$stacktrace
    )

#BEGIN (optional) runs once
BEGIN {

    $logfile = "$home\desktop\logfile.txt"
    remove-item -Path $logfile -ErrorAction Ignore
    new-item -Path $logfile -ItemType 'File'
}

#PROCESS can run multiple times
PROCESS {
    
    $timestamp = get-date
    
    # IMPORTANT: Read only first value!
    "   " | out-file $logfile -Append
    
    "____________________________________________________________________________________________________________" | out-file $logfile -Append
    
    "Error happend at: $timestamp on: $hostname - $env - $logicalname" | out-file $logfile -Append

    "Error message:             $errormsg"          | out-file $logfile -Append
    "Error exception:           $exception"         | out-file $logfile -Append
    "Failing script:            $scriptname"        | out-file $logfile -Append
    "Failing at line number:    $failinglinenumber" | out-file $logfile -Append
    "Failing at line:           $failingline"       | out-file $logfile -Append
    "Powershell command path:   $pscommandpath"     | out-file $logfile -Append
    "Position message:          $positionmsg"       | out-file $logfile -Append
    "Stack trace:               $stacktrace"        | out-file $logfile -Append
    
    "------------------------------------------------------------------------------------------------------------" | out-file $logfile -Append      
}

#END (optional) runs once
END {}  
}   
# SPECIFIC ERROR-HANDLING METHOD (END)   


# ===============================================================================================================================================================================
# ______________________________________________________________________________________________________________________________________________________________

# MAIN FUNCIONS 

# REBOOT
function reboot {
   
    # reboots pc
    restart-computer -Force
}

# ERROR_COUNT
function error_count {
              
    # error detected
    $error_counter += 1

    set-location -Path "$home\desktop"
        
    # writes $error_counter to logfile
    write-output $error_counter >> "$home\desktop\error_count.txt"
}

# ERROR_MESSAGE
function error_message {
    
    # tells user about error and appropriate follow-up actions to take
    write-output "Error encountered! If you have seen this error over three times, run Windows Repair/Recovery!"
    
    # waits for user keypress before calling reboot function
    read-host "Otherwise, reboot and run quick_clean.ps1 again!!!"
    reboot
}


#*********************************************************************************************************************
#***START MAIN SCRIPT*************************************************************************************************
#*********************************************************************************************************************

# TITLE
$title = "quick_clean.ps1"
$host.UI.RawUI.WindowTitle = $title

#BACKGROUNDCOLOR
$host.UI.RawUI.BackgroundColor = 'Black'

# MENU
function menu {
  
  # creates global variable to be used outside function
  $global:user_choice = $null

  # creates list of allowable menu choices
  $menu_options = 1, 2, 3, 4, 5, 6, "X"

  # waits for appropriate user choice
  while ($menu_options -notcontains $global:user_choice) {
    
    # CLEAR
    clear-host
      
    # wait for proper input
    write-host "PLEASE SELECT AN OPTION:"               -ForegroundColor 'White';       "";
    
    #1
    write-host "[1]"                                    -ForegroundColor 'Gray'         -NoNewline
    write-host " UPDATE | CLEAN | OPTIMIZE"             -ForegroundColor 'Cyan'         -NoNewline
    write-host " -no scandisk"                          -Foregroundcolor 'DarkGray'
    
    #2
    write-host "[2]"                                    -ForegroundColor 'Gray'         -NoNewline
    write-host " UPDATE | CLEAN | OPTIMIZE"             -ForegroundColor 'Cyan'         -NoNewline
    write-host " -quick scandisk"                       -Foregroundcolor 'DarkGray'
    
    #3
    write-host "[3]"                                    -ForegroundColor 'Gray'         -NoNewline
    write-host " UPDATE | CLEAN | OPTIMIZE"             -ForegroundColor 'Cyan'         -NoNewline
    write-host " -full scandisk"                        -Foregroundcolor 'DarkGray'

    # skips line
    "";
      
    #4
    write-host "[4]"                                    -ForegroundColor 'DarkGray'     -NoNewline
    write-host " AUTOMATED CLEAN | REBOOT*"             -Foregroundcolor 'Gray'         -NoNewline 
    write-host " -no scandisk"                          -Foregroundcolor 'DarkGray'
    
    #5
    write-host "[5]"                                    -ForegroundColor 'DarkGray'     -NoNewline
    write-host " AUTOMATED CLEAN | REBOOT*"             -Foregroundcolor 'Gray'         -NoNewline 
    write-host " -quick scandisk"                       -Foregroundcolor 'DarkGray'
    
    #6
    write-host "[6]"                                    -ForegroundColor 'DarkGray'     -NoNewline
    write-host " AUTOMATED CLEAN | REBOOT*"             -Foregroundcolor 'Gray'         -NoNewline 
    write-host " -full scandisk"                        -Foregroundcolor 'DarkGray'

    write-host " *  "                                   -ForegroundColor 'Gray'         -NoNewline
    write-host "Does not include updates"               -Foregroundcolor 'Gray';        "";
    
    #X
    write-host "[X] EXIT"                               -Foregroundcolor 'DarkRed';     "";
 
    # NoNewline method allows different colored text on same line
    write-host "Choice: " -ForegroundColor 'DarkCyan' -NoNewline
    # assigns user input to $global:user_choice variable
    $global:user_choice = read-host
  }
  
  # EXIT - if user selects "x" or "X"
  if ($global:user_choice -eq "X") {EXIT 0}
}


# ==========================================================================================================================
# IMPORTANT-->>To output any line to logfile.log, add this to the end of the line: " >> c:\users\public\desktop\logfile.log"
# ==========================================================================================================================

# call menu function
menu

# prompt user for deep clean option
if ($global:user_choice -eq 1 -or $global:user_choice -eq 2 -or $global:user_choice -eq 3) {
    
    $deep_options = "Y", "N"

    while ($deep_options -notcontains $deep_clean) {$deep_clean = read-host "Would you like to deep clean junk files(Y/N)"}
    "";
}

# print start time
$timestamp = get-date
write-output "Start Time:   " + $timestamp
"";    


# *******************************************************************************************************************************************************************************

# SYSTEM INFO
write-output "Please wait... Checking system information "
"";

write-output "================="
write-output "== SYSTEM INFO =="
write-output "================="

# bios info
Get-WmiObject -Class Win32_Bios | Format-List -Property *
"";

# os name
systeminfo.exe | Select-String -Pattern "OS Name" -CaseSensitive -SimpleMatch
"";

# os version
systeminfo.exe | Select-String -Pattern "OS Version" -CaseSensitive -SimpleMatch
"";

# pc name
wmic.exe cpu get name
"";

# gpu info
wmic.exe path win32_videocontroller get name
"";

# memory info
write-output "RAM"
systeminfo.exe | findstr.exe "Total Physical Memory"
"";

# system type
write-output "System"
systeminfo.exe | findstr.exe "System Type"
"";

# disk drive info
write-output "Disks"
wmic.exe diskdrive get name,model,size
"";

# network info
write-output "Network"
ipconfig.exe | findstr.exe IPv4 #IPv6
"";


# *****************************************************************************************************************************************************************************

# SYSTEM RESTORE
write-output "====================" 
write-output "== SYSTEM RESTORE ==" 
write-output "===================="

write-output "System Restore in progress..."

# creates system restore point named "quick_clean.ps1"
Checkpoint-Computer -Description "quick_clean.ps1" -RestorePointType MODIFY_SETTINGS 
"";

write-output "System Restore complete!"
"";

# ***CHKDSK******************************************************************************************************************************************************************************

# SCANDISK
set-location -Path "c:\windows\system32"

# sets user's selected scandisk option
if ($global:user_choice -eq 2 -or $global:user_choice -eq 5) {write-output Y | chkdsk.exe c: /x /f}
if ($global:user_choice -eq 3 -or $global:user_choice -eq 6) {write-output Y | chkdsk.exe c: /x /r}
"";


#"============================================================================================================================================================================================= *** 

# GPU FILES
write-output "**********************"
write-output "*** GPU INSTALLERS ***"
write-output "**********************"

# searches for old amd installer files and deletes if found
write-output "Searching for old AMD files to delete..."

if (test-path "c:\amd"){remove-item -Path "c:\amd" -Force -Recurse -Verbose} 
else {write-host "c:\amd does not exist" -ForegroundColor DarkGray}
"";

# searches for old nvidia installer files and deletes if found
write-output "Searching for old NVidia files to delete..."

if (test-path "c:\nvidia"){remove-item -Path "c:\nvidia" -Force -Recurse -Verbose} 
else {write-host "c:\nvidia folder does not exist" -ForegroundColor DarkGray}

if (test-path "c:\program files\nvidia corporation\installer2") {remove-item -Path "c:\program files\nvidia corporation\installer2" -Force -Recurse -Verbose} 
else {write-host "c:\program files\nvidia corporation\installer2 folder does not exist" -ForegroundColor DarkGray}
"";


#"============================================================================================================================================================================================== *** 

# MICROSOFT UPDATE - if user selected manual clean
if ($global:user_choice -eq 1 -or $global:user_choice -eq 2 -or $global:user_choice -eq 3) {

    write-output "************************"
    write-output "*** MICROSOFT UPDATE ***"
    write-output "************************"
    write-output "Searching for Microsoft Updates..."
    "";
    
    set-location -Path "c:\windows\system32"
  
    # Opens ms update window
    start-process ms-settings:windowsupdate-action
    
    # pauses 4 seconds
    wait-event -Timeout 4
    
    # checks for updates while ms update window is open
    start-process ms-settings:windowsupdate-action
       
    write-output "____________________________________________"
    write-output "|CHECK MICROSOFT STORE AND OPTIONAL UPDATES|"
    write-output "--------------------------------------------"

    # waits for keypress
    read-host "To close update windows, click this window and press <ENTER>"
    "";

    # closes microsoft update window
    get-process -Name 'systemsettings' -ErrorAction Ignore | stop-process -ErrorAction Ignore

    
<#>
# TODO automatically open/check microsoft store updates

    #write-output "***********************"
    #write-output "*** MICROSOFT STORE ***"
    #write-output "***********************"

    set-location -Path "C:\Program Files\WindowsApps"
    start-process "c:\program files\windowsapps\*.*\winstore.app.exe"

    $filepath = get-childitem -Path "c:\program files\windowsapps\" -Include "winstore.app.exe" -File -Recurse -Force -ErrorAction SilentlyContinue 
    start-process -FilePath $filepath -ErrorAction SilentlyContinue

    get-childitem  -Path "c:\program files\windowsapps\" -Name "winstore.app.exe"       -File -Recurse -Force -ErrorAction SilentlyContinue     | start-process -FilePath "c:\program files\windowsapps\*.*\winstore.app.exe" -ErrorAction SilentlyContinue
    get-childitem  -Path "c:\program files\windowsapps\" -Include *winstore.app.exe*    -File -Recurse -Force -ErrorAction SilentlyContinue     | start-process -FilePath "c:\program files\windowsapps\*.*\winstore.app.exe" -ErrorAction SilentlyContinue
    get-childitem  -Path "c:\program files\windowsapps\*winstore.app.exe"               -File -Recurse -Force -ErrorAction SilentlyContinue     | start-process -FilePath "c:\program files\windowsapps\*.*\winstore.app.exe" -ErrorAction SilentlyContinue
    get-childitem  -Path "c:\program files\windowsapps\*.winstore.app.exe"              -File -Recurse -Force -ErrorAction SilentlyContinue     | start-process -FilePath "c:\program files\windowsapps\*.*\winstore.app.exe" -ErrorAction SilentlyContinue
    # other options: -Exclude *.txt, *.tmp
    
    read-host
<#>
   

    # closes microsoft store window
    get-process -Name 'winstore.app' -ErrorAction Ignore | stop-process -ErrorAction Ignore
 

#*********************************************************************************************************************************************************************************

    # WINGET
    write-output "**************"
    write-output "*** WINGET ***"
    write-output "**************"
    "";

    # pauses 2 seconds
    wait-event -Timeout 2

    # runs winget list
    write-output * | winget.exe list
    "";

    # creates and nulls variables
    $winget_choice = $null
    $app_id = $null
    "";
    
    # loops until correct input
    while ($winget_choice -ne "Y" -or $winget_choice -ne "N") {
    
        # assigns user input to $winget_choice
        $winget_choice = read-host "Do you want to update any more apps(Y/N)"
        write-output                       "___________________________________________"
        "";

        # prompts user to update apps
        if ($winget_choice -eq "Y") {
        
            # awaits user to enter software id to update
            $app_id = read-host "Enter software ID"
            
            # updates user entered software id
            winget.exe upgrade $app_id
            "";
        }
        
        # exits loop if selected
        if ($winget_choice -eq "N") {break}   
    }
}
      

#=================================================================================================================================================================================

# spacing added to separate winget darkblue bg and custom black bg
"";
"";

# changed bg from darkblue (winget) back to black
$host.UI.RawUI.BackgroundColor = 'Black'
"";


# DISM
# CHECKHEALTH
write-output "************************"
write-output "*** DISM CHECKHEALTH ***"
write-output "************************"

# sets error level to zero
$error.Clear()

set-location -Path "c:\windows\system32"

# calls dism /checkhealth option
dism.exe /online /cleanup-image /checkhealth
"";

# $? = no error # (-not $?) = error
if (-not $?) {error_count; write_errorlog}


# runs /scanhealth option if /checkhealth option fails
if (-not $?) {

    # SCANHEALTH
    write-output "***********************"
    write-output "*** DISM SCANHEALTH ***"
    write-output "***********************"

    # sets error level to zero
    $error.Clear()

    set-location -Path "c:\windows\system32"

    # calls dism /scanhealth
    dism.exe /online /cleanup-image /scanhealth
    "";

    # checks for errors and logs if appropriate
    if (-not $?) {error_count; write_errorlog}


    # runs /restorehealth option if /scanhealth option fails
    if (-not $?) {

        # RESTOREHEALTH
        write-output "**************************"
        write-output "*** DISM RESTOREHEALTH ***"
        write-output "**************************"

        # sets error level to zero
        $error.Clear()

        set-location -Path "c:\windows\system32"

        # calls dism /restorehealth
        dism.exe /online /cleanup-image /restorehealth
        "";

        # checks for errors and logs if appropriate
        if (-not $?) {error_count; write_errorlog}
    }
}


#================================================================================================================================================================================

# COMPONENTCLEANUP
write-output "*****************************"
write-output "*** STARTCOMPONENTCLEANUP ***"
write-output "*****************************"

# sets error level to zero
$error.Clear()

set-location -Path "c:\windows\system32"

# calls dism /startcomponentcleanup
dism.exe /online /cleanup-image /startcomponentcleanup
"";

# checks for errors and logs if appropriate
if (-not $?) {error_count; write_errorlog}


#*******************************************************************************************************************************************************

# SFC
$sfc_choice = $null

# prompt user to run sfc scan
if ($global:user_choice -eq 1 -or $global:user_choice -eq 2 -or $global:user_choice -eq 3) {
    while ($sfc_choice -ne "Y" -and $sfc_choice -ne "N") {$sfc_choice = read-host "Run System File Checker(Y/N)?"}
}

#runs sfc if selected by user or if auto clean mode was selected by user
if ($sfc_choice -eq "Y" -or $global:user_choice -eq 4 -or $global:user_choice -eq 5 -or $global:user_choice -eq 6) {

    write-output "***************************"
    write-output "*** SYSTEM FILE CHECKER ***"
    write-output "***************************"

    # sets error level to zero
    $error.Clear()

    set-location -Path "c:\windows\system32"

    # calls sfc scanner
    sfc.exe /scannow
    "";

    # checks for errors and logs if appropriate
    if (-not $?) {error_count; write_errorlog}
}


#==============================================================================================================================================================================================

#DEFRAG
write-output "***********************"
write-output "*** OPTIMIZE/DEFRAG ***"
write-output "***********************"

# sets error level to zero
$error.Clear()

set-location -Path "c:\windows\system32"

# /c = AllVolumes | /h = /NormalPriority (default=Low) | /o = Optimize (perform proper optimization for each media type)
defrag.exe c: d: /h /o 
#start-process -FilePath defrag.exe -ArgumentList 'c: d: /h /o' -Wait -Verbose
"";

# checks for errors and logs if appropriate
if (-not $?) {error_count; write_errorlog}


#==============================================================================================================================================================================================

# CCLEANER
write-output "____________"
write-output "| CCLEANER |"
write-output "============"

# sets error level to zero
$error.Clear()

# REQUIRED: first install ccleaner
write-output "Please wait... CCleaner running"

set-location -Path "c:\program files\ccleaner" -ErrorAction Ignore

# calls ccleaner to run
start-process ccleaner.exe /auto -ErrorAction Ignore

# pauses host for 5 seconds
wait-event -Timeout 5

"";


#==============================================================================================================================================================================================

# skips diskclean to avoid duplicate run if deep clean was selected by user
if ($deep_clean -eq "N") {

  # runs full disk clean /sagerun if manual clean selected by user
  if ($global:user_choice -eq 1 -or $global:user_choice -eq 2 -or $global:user_choice -eq 3) {

    # DISKCLEAN
    write-output "___________"
    write-output "|DISKCLEAN|"
    write-output "==========="

    # REQUIRED --> Run ADMIN cmd one time: cleanmgr.exe /sageset:1

    # sets error level to zero
    $error.Clear()

    write-output "Cleaning Temporary Files..."
    write-output "(Move mouse over Disk Cleanup window if stuck)"

    # start disk cleaner
    set-location -Path "c:\windows\system32"
    
    #cleanmgr.exe /sagerun:1
    start-process -FilePath cleanmgr.exe -ArgumentList '/sagerun:1' -Wait -Verbose

    #wait-event -Timeout 12

    # minimizes all windows
    $x = New-Object -ComObject Shell.Application
    $x.minimizeall()

    # moves cursor to center of 1920x1080 screen if nircmd is installed
    nircmd setcursor 960 540
    nircmd movecursor 20 0

    # restores window sizes
    $x = New-Object -ComObject Shell.Application
    $x.UndoMinimizeAll()

    # checks for errors and logs if appropriate
    if (-not -$?) {error_count; write_errorlog}
  } 

  else {
    
    # sets error level to zero
    $error.Clear()
    
    # calls disk cleaner /autoclean if auto clean selected by user
    cleanmgr.exe /autoclean
    
    # checks for errors and logs if appropriate
    if (-not -$?) {error_count; write_errorlog} 
  }
}

# DEEP_CLEAN - runs deep_clean.ps1 if selected by user
elseif ($deep_clean -eq "Y") {& "$PSScriptRoot\deep_clean.ps1"}


# ****************************************************************************************************************************************************************************************

#END HEADER
write-output "________________________________________________________"
write-output "________________________________________________________"
"";

# END TIME
write-output "End Time"
$timestamp = get-date
write-output $timestamp
"";


# REBOOT
write-output "===================================="
write-output "TO FINISH OPTIMIZATION (RECOMMENDED)"
write-output "===================================="

# if auto clean was selected, tells user 20 second timer til reboot
if ($global:user_choice -eq 4 -or $global:user_choice -eq 5 -or $global:user_choice -eq 6) {write-output "Waiting 20 seconds to automatically reboot!"; wait-event -Timeout 20}

# if manual clean was selected, tells user to press <ENTER> to reboot
if ($global:user_choice -eq 1 -or $global:user_choice -eq 2 -or $global:user_choice -eq 3) {read-host "Press <ENTER> to reboot"}

# calls reboot function
reboot
