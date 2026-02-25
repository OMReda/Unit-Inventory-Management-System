
$csv = "inventory.csv"
$exe = ".\inventory.exe"

function Run-Sort($choice) {
    # Send choice, then Enter for the pause, then 0 to exit
    # Use Out-String to avoid pipeline issues
    $inputStr = "$choice`n`n0`n"
    $inputStr | &$exe > $null
    Get-Content $csv
    Write-Host "---"
}

# Setup test data
"500,Apple,10.0,5" | Out-File -FilePath $csv -Encoding ascii
"1,Zebra,50.0,2" | Out-File -FilePath $csv -Append -Encoding ascii
"50,Banana,5.0,10" | Out-File -FilePath $csv -Append -Encoding ascii

Write-Host "INITIAL DATA (Apple ID 500, Zebra ID 1, Banana ID 50):"
Get-Content $csv
Write-Host "---"

Write-Host "ID SORT (Result should be 1, 50, 500):"
Run-Sort 6

Write-Host "NAME SORT (Result should be Apple, Banana, Zebra):"
Run-Sort 7

Write-Host "PRICE SORT (Result should be 5.0, 10.0, 50.0):"
Run-Sort 8

# Restore user data
"1,REAL,500.0,200" | Out-File -FilePath $csv -Encoding ascii
"50,traaa,200.0,50" | Out-File -FilePath $csv -Append -Encoding ascii
