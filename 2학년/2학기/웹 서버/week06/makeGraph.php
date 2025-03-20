<meta charset="utf-8">
<link rel="StyleSheet" href="./table.css" type="text/css"/>
<h2 style="text-align: center;">-학생 별 과목 점수 종합-</h2><br>
<?php
// 데이터 파일 읽기
$myfile = fopen("data.txt", "r") or die("파일을 열 수 없습니다!");
$jsonData = fread($myfile, filesize("data.txt"));
fclose($myfile);

$data = json_decode($jsonData, true);
$subject = array("국어", "영어", "수학", "과학", "역사");

// URL에서 sn 값 받기
$sn = isset($_GET['sn']) ? $_GET['sn'] : null;

?>

<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
<script type="text/javascript">
    google.charts.load('current', { 'packages': ['corechart', 'bar'] });
    google.charts.setOnLoadCallback(drawChart);

    function drawChart() {
        <?php
        // 특정 학생의 성적을 표시 (URL에 sn이 있을 때)
        if ($sn !== null && isset($data[$sn])) {
            $scores = $data[$sn];

            // 평균, 최대, 최소 계산
            $avg = [];
            $max = [];
            $min = [];
            foreach ($subject as $subj) {
                $avg[$subj] = round(array_sum(array_column($data, $subj)) / count($data));
                $max[$subj] = max(array_column($data, $subj));
                $min[$subj] = min(array_column($data, $subj));
            }
            ?>
            var data = google.visualization.arrayToDataTable([
                ['과목', '점수', '평균', '최대', '최소'],
                <?php
                foreach ($subject as $subj) {
                    echo "['" . $subj . "', " . $scores[$subj] . ", " . $avg[$subj] . ", " . $max[$subj] . ", " . $min[$subj] . "],\n";
                }
                ?>
            ]);

            var options = {
                title: '학생 <?= $sn ?> 성적',
                hAxis: {
                    title: '과목',
                },
                vAxis: {
                    title: '점수',
                },
                isStacked: false,
                colors: ['#1b9e77', '#d95f02', '#7570b3', '#e7298a'], // 각 점수 색상
            };

            var chart = new google.visualization.ColumnChart(document.getElementById('chart_div'));
            chart.draw(data, options);
            <?php
        }
        // 모든 학생의 성적을 표시 (URL에 sn이 없을 때)
        else {
            foreach ($data as $studentNumber => $scores) {
                // 평균, 최대, 최소 계산
                $avg = [];
                $max = [];
                $min = [];
                foreach ($subject as $subj) {
                    $avg[$subj] = round(array_sum(array_column($data, $subj)) / count($data));
                    $max[$subj] = max(array_column($data, $subj));
                    $min[$subj] = min(array_column($data, $subj));
                }
                ?>
                var data<?= $studentNumber ?> = google.visualization.arrayToDataTable([
                    ['과목', '점수', '평균', '최대', '최소'],
                    <?php
                    foreach ($subject as $subj) {
                        echo "['" . $subj . "', " . $scores[$subj] . ", " . $avg[$subj] . ", " . $max[$subj] . ", " . $min[$subj] . "],\n";
                    }
                    ?>
                ]);

                var options = {
                    title: '학생 <?= $studentNumber ?> 성적',
                    hAxis: {
                        title: '과목',
                    },
                    vAxis: {
                        title: '점수',
                    },
                    isStacked: false,
                    colors: ['#1b9e77', '#d95f02', '#7570b3', '#e7298a'], // 각 점수 색상
                };

                var chart = new google.visualization.ColumnChart(document.getElementById('chart_div_<?= $studentNumber ?>'));
                chart.draw(data<?= $studentNumber ?>, options);
                <?php
            }
        }
        ?>
    }
</script>

<?php
// 특정 학생 차트만 생성 (sn이 있을 때)
if ($sn !== null && isset($data[$sn])) {
    echo "<div id='chart_div' style='width: 800px; height: 500px;'></div>";
}
// 모든 학생의 차트 생성 (sn이 없을 때)
else {
    foreach ($data as $studentNumber => $scores) {
        echo "<div id='chart_div_$studentNumber' style='width: 800px; height: 500px;'></div>";
    }
}
?>
