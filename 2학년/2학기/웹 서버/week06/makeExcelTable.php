<meta charset="utf-8">
<link rel="StyleSheet" href="./table.css" type="text/css"/>

<?php
// XML 파일(scores.xml) 불러오기
$dom = new DOMDocument();
$dom->load('scores.xml');

// XML 파일의 행(Row)과 셀(Cell) 데이터를 가져오기
$rows = $dom->getElementsByTagName("Row");

// 첫 번째 행의 데이터를 통해 과목명을 설정
$headerRow = $rows->item(0);
$headerCells = $headerRow->getElementsByTagName("Cell");

// 테이블 헤더 출력 
echo "<table border='1'>";
echo "<thead><tr><th></th>";
foreach ($headerCells as $headerCell) {
    echo "<th>" . $headerCell->getElementsByTagName("Data")->item(0)->nodeValue . "</th>";
}
echo "</tr></thead>";
echo "<tbody>";

// 두 번째 행부터는 학생 데이터 출력
for ($i = 1; $i < $rows->length; $i++) {
    $row = $rows->item($i);
    $cells = $row->getElementsByTagName("Cell");

    // 첫 번째 셀은 학번으로 링크 추가
    $studentId = $cells->item(0)->getElementsByTagName("Data")->item(0)->nodeValue;
    echo "<tr><td><a href='./makeGraph.php?sn=" . $studentId . "' target='_blank'>" . $studentId . "</a></td>";

    // 과목별 점수 출력
    for ($j = 1; $j < $cells->length; $j++) {
        $score = $cells->item($j)->getElementsByTagName("Data")->item(0)->nodeValue;
        echo "<td>" . $score . "</td>";
    }
    echo "</tr>";
}

echo "</tbody>";
echo "</table>";
?>
