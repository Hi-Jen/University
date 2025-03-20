<meta charset="utf-8">
<link rel="StyleSheet" href="./table.css" type="text/css"/>

<?php
function makeTable($type, $ST, $ET) {
    $str = "";
    $width = 6 * 160;
    if ($type == "B") $width += 160;

    $str .= "<table width='" . $width . "'>";
    $str .= "<colgroup>";
    for ($i = 0; $i < 5; $i++) $str .= "<col width='160'>";
    if ($type == "B") $str .= "<col width='160'>";
    $str .= "</colgroup>";

    $str .=  "<tr>";
    $str .= "<th>시간</th><th>월</th><th>화</th><th>수</th><th>목</th><th>금</th>";
    if ($type == "B") $str .=  "<th>토</th>";
    $str .= "</tr>";

    for ($j = $ST; $j < $ET; $j++) {
        $str .=  "<tr>";
        $str .=  "<td align='center'>" . $j . ":00 ~ " . ($j + 1) . ":00</td>";
        for ($i = 0; $i < 5; $i++) $str .=  "<td></td>";
        if ($type == "B") $str .=  "<td></td>";
        $str .=  "</tr>";
    }
    $str .=  "</table>";

    return $str;
}
?>

<?php
// Get values from GET request
$type = $_GET['type']; // A: 월~금, B: 월~토
$ST = $_GET['start']; // 시작 시간
$ET = $_GET['end']; // 끝 시간

echo makeTable($type, $ST, $ET);
?>
