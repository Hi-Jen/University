<?php
include 'db.php';

$vote_id = 1;

$results_query = "SELECT options.option_text, COUNT(user_votes.option_id) AS vote_count
                  FROM options
                  LEFT JOIN user_votes ON options.option_id = user_votes.option_id
                  WHERE options.vote_id = $vote_id
                  GROUP BY options.option_id";
$results = $conn->query($results_query);
$data = [];
while ($row = $results->fetch_assoc()) {
    $data[] = $row;
}
$conn->close();
?>
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>투표 결과</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<body>
    <div class="container">
        <h1>투표 결과</h1>
        <canvas id="voteChart"></canvas>
    </div>
    <script>
        const data = {
            labels: <?php echo json_encode(array_column($data, 'option_text')); ?>,
            datasets: [{
                label: '투표 수',
                data: <?php echo json_encode(array_column($data, 'vote_count')); ?>,
                backgroundColor: ['rgba(54, 162, 235, 0.5)', 'rgba(255, 99, 132, 0.5)', 'rgba(75, 192, 192, 0.5)'],
            }]
        };
        const config = {
            type: 'bar',
            data: data,
        };
        new Chart(document.getElementById('voteChart'), config);
    </script>
</body>
</html>
