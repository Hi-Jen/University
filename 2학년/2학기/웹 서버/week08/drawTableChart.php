<?php
$conn = mysqli_connect('localhost', 'root', 'admin#2024');
if (!mysqli_select_db($conn, 'DB20213032')) {
    die("Can't use foo : " . mysqli_error($conn));
} else {
    $sql = "SELECT sname, sid, sdept, q1, q2, q3, q4, q4a FROM poll";
    $result = $conn->query($sql);

    echo "<style>
            table {
                width: 100%;
                border-collapse: collapse;
                text-align: center;
                font-family: Arial, sans-serif;
            }
            th, td {
                padding: 10px;
                border: 1px solid #ccc;
            }
            th {
                background-color: #e0f7f9;
                color: black;
                font-weight: bold;
            }
            tr:nth-child(even) {
                background-color: #f9f9f9;
            }
            tr:nth-child(odd) {
                background-color: #ffffff;
            }
            
        </style>";

    echo "<table>";
    echo "<tr><th>이름</th><th>학번</th><th>학과명(전공)</th><th>자신감</th><th>이해도</th><th>경험</th><th style='color:lightgray;'>활동(선택)</th><th style='color:lightgray;'>활동(기타)</th><th>수정</th></tr>";

    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            echo "<tr>";
            echo "<td>" . $row["sname"] . "</td>";
            echo "<td>" . $row["sid"] . "</td>";
            echo "<td>" . $row["sdept"] . "</td>";
            echo "<td>" . $row["q1"] . "</td>";
            echo "<td>" . $row["q2"] . "</td>";
            echo "<td>" . $row["q3"] . "</td>";
            echo "<td>" . ' ' . "</td>";
            echo "<td>" . $row["q4a"] . "</td>";
            echo "<td><a href='update.php?sid=" . $row["sid"] . "' style='color:blue;'>수정</a></td>";
            echo "</tr>";
        }
    }
    echo "</table>";
}
?>