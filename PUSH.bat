:: Get date and time
set "raw_date=%date%"
set "raw_time=%time%"

:: Replace problematic characters in time
set "raw_time=%raw_time::=_%"
set "raw_time=%raw_time:.=_%"
set "raw_time=%raw_time: =0%"

:: Replace slashes in date
set "raw_date=%raw_date:/=-%"
set "raw_date=%raw_date: =%"

:: Concatenate into one string
set "datetime_str=%raw_date%_%raw_time%"

echo %datetime_str%

git add .
git commit -m %datetime_str%
git push -u origin main

pause