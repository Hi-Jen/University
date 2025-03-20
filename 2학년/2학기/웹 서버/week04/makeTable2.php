<meta charset="utf-8">
<link rel="stylesheet" href="./table.css" type="text/css" />
<?php include("./data2.php"); ?>


<?php
echo '<div style="text-align: center; font-size: 20px;"><p>20213032 권영훈</p>';
function makeTimeTableStudent($data, $grade) {
    $time = array('', '1교시<br>(09:00 ~ 09:50)', '2교시<br>(10:00 ~ 10:50)', '3교시<br>(11:00 ~ 11:50)',
        '4교시<br>(12:00 ~ 12:50)', '5교시<br>(13:00 ~ 13:50)', '6교시<br>(14:00 ~ 14:50)',
        '7교시<br>(15:00 ~ 15:50)', '8교시<br>(16:00 ~ 16:50)', '9교시<br>(17:00 ~ 17:50)');
   
    $day = array("월", "화", "수", "목", "금"); // 요일 배열
    $str = "<table width=\"" . (180 * 6) . "px\">";
    $spancount = array(0, 0, 0, 0, 0, 0);

    // 첫 번째 행: 요일 헤더
    $str .= "<tr align=\"center\">";
    $str .= "<td bgcolor=\"#E0FFFF\">교시</td>"; // 시간 열 추가
    foreach ($day as $d) {
        $str .= "<td bgcolor=\"#E0FFFF\" align=\"center\">" . $d . "</td>"; // 요일 추가
    }
    $str .= "</tr>";

    // 각 교시별 수업 내용 생성
    for ($i = 1; $i < 10; $i++) {
        $str .= "<tr align=\"center\">"; // 각 교시에 대한 새로운 행 시작
        $str .= "<td bgcolor=\"lightyellow\">" . $time[$i] . "</td>"; // 시간 셀

        for ($j = 1; $j < 6; $j++) {
            if ($spancount[$j] > 0) {
                $spancount[$j]--;
                continue;
            }
      
            if (empty($data[$j][$i])) {
                $str .= "<td></td>";
                continue;
            }
      
            $exist = false;
            foreach ($data[$j][$i] as $d) {
                if ($d[0] != $grade) continue;
                $exist = true;
              
                // 지도교수멘토링만 표시
                if ($d[1] == "지도교수멘토링") {
                    $str .= "<td rowspan=\"" . $d[3] . "\">" . $d[1] . "</td>";
                } else if ($d[1] && $d[2]) {
                    $str .= "<td rowspan=\"" . $d[3] . "\">";
                    $spancount[$j] = $d[3] - 1;
                    $str .= $d[1] . "<br/>" . $d[2] . "교수<br/>강의실: " . ($d[4] ? $d[4] : "미정") . "</td>";
                } else {
                    $str .= "<td></td>";
                }
            }
      
            if (!$exist) {
                $str .= "<td></td>";
            }
        }
        $str .= "</tr>"; // 각 교시에 대한 행 닫기
    }

    $str .= "</table>"; // 테이블 닫기
    return $str;
}


echo makeTimeTableStudent($class, $_GET['grade']);
?>