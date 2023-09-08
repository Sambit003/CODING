<#
.SYNOPSIS
    Compiles and executes a C source code file.
.DESCRIPTION
    This script compiles a C source code file using GCC (or a user-specified compiler) and executes the resulting executable.
    You can either specify the source code file path, use the auto-detect option to find
    the most recently changed C file, or enter code manually in the terminal.
.PARAMETER autoDetect
    Use this switch to automatically detect the most recently changed C source code file
    in the current directory and its subdirectories.
.PARAMETER sourceFilePath
    Specify the path to the C source code file that you want to compile and execute.
.PARAMETER help
    Use this switch to display this help message.
.PARAMETER compiler
    Specify the C compiler to use (e.g., "gcc", "clang", "msvc"). Default is "gcc".

    Examples:
    -compiler gcc          (Use GCC as the compiler)
    -compiler clang        (Use Clang as the compiler)
    -compiler msvc         (Use MSVC as the compiler)
.PARAMETER formatCode
    Use this switch to enable code formatting with clang-format before compilation (only for manual mode).
.PARAMETER downloadClangFormat
    Use this switch to download clang-format (if not installed) for code formatting. Default is $true.
.PARAMETER log
    Use this switch to log compilation and execution results to a file in the script's parent directory.
.PARAMETER setAsDefaultCompiler
    Use this switch to set the currently used compiler as the default compiler. Default is No.
.EXAMPLE
    .\compile.ps1 -autoDetect
    This command will automatically detect the most recently changed C source code file
    in the current directory and its subdirectories, compile, and execute it using the default compiler (gcc).
.EXAMPLE
    .\compile.ps1 -sourceFilePath C:\Path\To\Your\File.c
    This command will compile and execute the specified C source code file using the default compiler (gcc).
.EXAMPLE
    .\compile.ps1 -log
    This command will log the compilation and execution results to a file named "compile.log" in the script's directory.
.EXAMPLE
    .\compile.ps1 -compiler gcc
    This command will compile and execute using GCC as the compiler.
.EXAMPLE
    .\compile.ps1 -compiler clang
    This command will compile and execute using Clang as the compiler.
.EXAMPLE
    .\compile.ps1 -compiler msvc
    This command will compile and execute using MSVC as the compiler.
.EXAMPLE
    .\compile.ps1 -manual
    This command will allow you to enter C code manually in the terminal, compile, and execute it using the default compiler (gcc).
.EXAMPLE
    .\compile.ps1 -manual -formatCode
    This command will enable code formatting using clang-format before compilation (only for manual mode).
.EXAMPLE
    .\compile.ps1 -manual -downloadClangFormat
    This command will download clang-format (if not installed) for code formatting (only for manual mode).
.EXAMPLE
    .\compile.ps1 -setAsDefaultCompiler
    This command will set the currently used compiler as the default compiler for future compilations.
#>

param (
    [switch]$autoDetect,
    [string]$sourceFilePath,
    [switch]$manual,
    [switch]$help,
    [string]$compiler = "gcc",
    [switch]$formatCode,
    [bool]$downloadClangFormat = $False,
    [switch]$log,
    [switch]$setAsDefaultCompiler
)

function CompileAndExecute {
    param (
        [string]$sourceFilePath,
        [string]$compiler
    )
    if (Test-Path -Path $sourceFilePath -PathType Leaf) {
        $sourceDirectory = [System.IO.Path]::GetDirectoryName($sourceFilePath)
        $sourceFileNameWithoutExt = [System.IO.Path]::GetFileNameWithoutExtension($sourceFilePath)
        $executableName = "${sourceDirectory}\${sourceFileNameWithoutExt}.exe"
        
        if ($formatCode) {
            if ($downloadClangFormat -eq "Yes") {
                choco install clang-format -y
            }
            clang-format -i $sourceFilePath
        }

        $compileCommand = "$compiler $sourceFilePath -o '$executableName'"
        Invoke-Expression -Command $compileCommand
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Compilation successful. Executing $executableName..."
            Start-Process -FilePath $executableName -NoNewWindow -Wait
            Remove-Item -Path $executableName -Force
        } else {
            Write-Host "Compilation failed. Check the C code for errors."
        }
    } else {
        Write-Host "The specified source file does not exist."
    }
}


if ($help) {
    Get-Help $MyInvocation.MyCommand.Definition
    return
} elseif ($autoDetect) {
    $mostRecentCFile = Get-ChildItem -Path . -Filter *.c -File -Recurse | Sort-Object LastWriteTime | Select-Object -Last 1
    if ($mostRecentCFile -ne $null) {
        $sourceFilePath = $mostRecentCFile.FullName
        Write-Host "Automatically detected source file: $sourceFilePath"
        CompileAndExecute -sourceFilePath $sourceFilePath -compiler $compiler
    } else {
        Write-Host "No C source files found in the current directory or its subdirectories."
    }
} elseif ($sourceFilePath) {
    CompileAndExecute -sourceFilePath $sourceFilePath -compiler $compiler
} elseif ($manual) {
    $tempFile = ".\temp.c"
    Write-Host "Enter your C code below. To save and exit, press Enter on an empty line."
    $lines = @()
    while ($true) {
        $line = Read-Host
        if ($line -eq "") {
            break
        }
        $lines += $line
    }
    $lines | Set-Content -Path $tempFile
    
    if (Test-Path -Path $tempFile -PathType Leaf) {
        $sourceFilePath = $tempFile
        Write-Host "Compilation started..."
        CompileAndExecute -compiler "gcc" -sourceFilePath $sourceFilePath
    } else {
        Write-Host "No code entered. Exiting."
    }
} else {
    Get-Help $MyInvocation.MyCommand.Definition
    return
}

if ($log) {
    # New line
    Write-Host "`n`n Logging is enabled."
    $scriptDirectory = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent
    $logFilePath = Join-Path -Path $scriptDirectory -ChildPath "compile.log"    
    if (-not (Test-Path -Path $logFilePath -PathType Leaf)) {
        New-Item -Path $logFilePath -ItemType File | Out-Null
    }
    $logContent = "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') - Compilation and execution started. Source file: $sourceFilePath, Compiler: $compiler"  
    if ($formatCode) {
        $logContent += ", Code formatting: Yes"
    } else {
        $logContent += ", Code formatting: No"
    }
    if ($downloadClangFormat) {
        $logContent += ", Download clang-format: Yes"
    } else {
        $logContent += ", Download clang-format: No"
    }
    if ($autoDetect) {
        $logContent += ", Auto-detect: Yes"
    } else {
        $logContent += ", Auto-detect: No"
    }
    if ($manual) {
        $logContent += ", Manual: Yes"
    } else {
        $logContent += ", Manual: No"
    }
    $logContent | Out-File -Append -FilePath $logFilePath
    if ($($LASTEXITCODE -eq 0)){
        $logContent = "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') - Compilation and execution completed. Source file: $sourceFilePath, Compiler: $compiler, Status: $($LASTEXITCODE -eq 0)"
    } else{
        $logContent = "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') - Compilation and execution failed. Source file: $sourceFilePath, Compiler: $compiler, Status: $($LASTEXITCODE -eq 0)"
    }
    $logContent | Out-File -Append -FilePath $logFilePath
} else{
    Write-Host "`n`nLogging is disabled."
}

if ($setAsDefaultCompiler) {
    Write-Host "Set $compiler as the default compiler for future compilations? (Yes/No):"
    $choice = Read-Host
    if ($choice -eq "Yes") {
        Set-Variable -Name "compiler" -Value $compiler -Scope Global
        Write-Host "$compiler set as the default compiler."
    }
}

if ($manual) {
    Remove-Item -Path $sourceFilePath -Force
}