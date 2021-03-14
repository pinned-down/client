# Build game.
$OutputDirectory = "C:/Users/npruehs/Desktop/test"

Write-Output "Starting UAT..."
C:\Dev\UE_4.26\Engine\Binaries\DotNET\AutomationTool.exe -ScriptsForProject=C:/Dev/pinned-down/client/PinnedDown.uproject BuildCookRun -nocompileeditor -installed -nop4 -project=C:/Dev/pinned-down/client/PinnedDown.uproject -cook -stage -archive -archivedirectory="$OutputDirectory" -package -ue4exe=C:\Dev\UE_4.26\Engine\Binaries\Win64\UE4Editor-Cmd.exe -pak -prereqs -nodebuginfo -targetplatform=Win64 -build -target=PinnedDown -clientconfig=Development -utf8output

# Add version file.
$CurrentBranch = git rev-parse --abbrev-ref HEAD
$RevisionCount = git rev-list --count $CurrentBranch
$VersionFilePath = "$OutputDirectory/WindowsNoEditor/version.txt"

Write-Output "`nWriting file $VersionFilePath ..." 
"0.1.$RevisionCount" | Out-File $VersionFilePath
