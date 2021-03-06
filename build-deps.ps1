# Based on a script from CommitteeOfZero/impacto
param(
    [ValidateSet("Debug", "Release")][string]$BuildType = "Debug",
    [string]$BuildLocation = "build",
	[string]$SrcDir = ".",
    [ValidateSet("x64", "x86")][string]$Arch = "x64",
    [string]$VcpkgDir = $env:VCPKG_INSTALLATION_ROOT
)

function SetEnv() {
    $vswhere = "${env:ProgramFiles(x86)}/Microsoft Visual Studio/Installer/vswhere.exe"
    $ip = & $vswhere -prerelease -latest -property InstallationPath
    if ($ip -and (test-path "$ip\Common7\Tools\vsdevcmd.bat")) {
        & "${env:COMSPEC}" /s /c "`"$ip\Common7\Tools\vsdevcmd.bat`" -arch=x64 -no_logo && set" | foreach-object {
            $name, $value = $_ -split '=', 2
            set-content env:\"$name" $value
        }
    }
}

function GenerateProjectFiles() {
	Write-Output "Generating project files..."
    if (!(Get-Command cmake -ErrorAction SilentlyContinue)) {
        SetEnv
    }
    $bargs = @( 
    "-DCMAKE_TOOLCHAIN_FILE=$VcpkgDir\scripts\buildsystems\vcpkg.cmake",
    "-DCMAKE_BUILD_TYPE=`"$BuildType`"", 
    "-DTARGET_ARCH=$Arch",
    "-DVCPKG_TARGET_TRIPLET=$Arch-windows",
	"-B$BuildLocation",
    "$SrcDir")
    & cmake $bargs
	
	Write-Output "Finished generating project files."
}

function InstallPackages() {
	Write-Output "Installing dependencies..."
    $vcpkg = "$VcpkgDir/vcpkg.exe"
    if (!(Get-Command $vcpkg -ErrorAction SilentlyContinue)) {
        $vcpkg = "vcpkg"
    }
    if (!(Get-Command $vcpkg  -ErrorAction SilentlyContinue)) {
        if (!(Test-Path build/vcpkg)) {
            mkdir build -Force | Out-Null
            Push-Location build
            & git clone https://github.com/Microsoft/vcpkg.git --depth 1
            Push-Location vcpkg
            ./bootstrap-vcpkg -disableMetrics
            Pop-Location
            Pop-Location
        }
        $vcpkg = "build/vcpkg/vcpkg.exe"
        $local_vcpkg = $true
    }

    & $vcpkg install sdl2 sdl2-image[libjpeg-turbo,libwebp,tiff] sdl2-ttf sdl2-mixer rapidjson zlib python3 fmt --triplet $Arch-windows
    if ($local_vcpkg) {
        & $vcpkg integrate install
        Write-Output "Cleaning up..."
        Remove-Item build/vcpkg/downloads -Recurse
        Remove-Item build/vcpkg/buildtrees -Recurse
    }
	Write-Output "Dependencies installed."
}

# I don't care about errors or warnings cringe
InstallPackages
GenerateProjectFiles