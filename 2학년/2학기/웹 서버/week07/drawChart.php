<html>
  <head>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {'packages':['table']});
      google.charts.setOnLoadCallback(drawTable);

      function drawTable() {
        var data = new google.visualization.DataTable();
        data.addColumn('string', '학번');  // 학번
        data.addColumn('number', '국어');  // 국어
        data.addColumn('number', '영어');  // 영어
        data.addColumn('number', '수학');  // 수학
        data.addColumn('number', '과학');  // 과학
        data.addColumn('number', '역사');  // 역사

        data.addRows([
          <?php
          // 데이터베이스 연결
          $conn = mysqli_connect('localhost', 'root', 'tv591100');
          if (!$conn) die('Could not connect: ' . mysqli_error($conn));
          if (!mysqli_select_db($conn, 'week07')) die('Can\'t use database: ' . mysqli_error($conn));

          // 데이터베이스에서 데이터 가져오기
          $sql = "SELECT * FROM data";
          $result = mysqli_query($conn, $sql);
          
          if ($result) {
              // Google 차트에서 필요한 형식으로 출력
              while ($row = mysqli_fetch_assoc($result)) {
                  echo "['" . $row['uid'] . "', " . $row['kor'] . ", " . $row['eng'] . ", " . $row['math'] . ", " . $row['sci'] . ", " . $row['hist'] . "],\n";
              }
          } else {
              echo 'Error fetching data: ' . mysqli_error($conn);
          }

          mysqli_close($conn);
          ?>
        ]);

        var table = new google.visualization.Table(document.getElementById('table_div'));
        table.draw(data, {showRowNumber: true, width: '100%', height: '100%'});
      }
    </script>
  </head>
  <body>
    <div id="table_div"></div>
  </body>
</html>