$directoryPath = Get-Location
$exeFiles = Get-ChildItem -Path $directoryPath -Filter *.exe -Recurse
foreach ($file in $exeFiles) {
    Write-Host "Removing $($file.FullName)"
    Remove-Item -Path $file.FullName -Force
}
Write-Host "Execution completed. All .exe files removed."
