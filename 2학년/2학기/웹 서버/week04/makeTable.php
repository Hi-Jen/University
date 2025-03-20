<meta charset="utf-8">
<link rel="StyleSheet" href="./table.css" type="text/css" />
<?php include("./data.php"); ?>

<?php
  function makeTimeTableStudent($data, $grade) { // L은 여기서만 사용되는 로컬을 의미함. G는 생략
    $time = array('', '(09:00 ~ 09:50)', '(10:00 ~ 10:50)', '(11:00 ~ 11:50)',
      '(12:00 ~ 12:50)', '(13:00 ~ 13:50)', '(14:00 ~ 14:50)', '(15:00 ~ 15:50)',
      '(16:00 ~ 16:50)', '(17:00 ~ 17:50)', );
    $day = array("월", "화", "수", "목", "금", );
    $str = "";
    $str .= "<table width=" . (180*6) . "px>";
    $spancount = array(0, 0, 0, 0, 0, 0);

    // 코드 추가!!
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

    
    $str .= "</table>";
    return $str;
  }
?>
<?php
  echo makeTimeTableStudent($class, $_GET['grade']);
?>