#!/bin/bash
  
#以YYYYMMDD格式输出大于等于第一个输入日期，小于等于二个输入日期的所有日期
  
begin_date=$1  
end_date=$2
  
while [ "$begin_date" != "$end_date" ]  
do 
echo $begin_date  
let begin_date=`date -d "-1 days ago ${begin_date}" +%Y%m%d` 
done
echo $end_date 
