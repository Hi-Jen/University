<?php

$conn = new mysqli('localhost', 'root', 'admin#2024');

$sid = $_GET['sid'];
$sql = "SELECT * FROM poll WHERE sid = '$sid'";
mysqli_select_db($conn, 'DB20213032');
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    $q4 = json_decode($row['q4'], true); 
    $q4a = htmlspecialchars($row['q4a']);
} else {
    die("해당 학생의 데이터가 없습니다.");
}
$conn->close();
?>

<!DOCTYPE html>
<html>

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <link rel="stylesheet" href="poll.css">
</head>

<body>
    <form method="POST" action="./updateReply.php">
        <div class="pollBorder">
            <h1 style="text-align: center;">설문지</h1>
            <h2 style="text-align: center;">(자가 진단 테스트)</h2>
            <div class="grayBox">
                <p class="grayBoxText">※아래 질문은 실력테스트용이 아닌 객관적 판단을 위한 설문지오니, 사실 그대로 적어주시면 됩니다.</p>
            </div>
            <div>
                <div class="Pinfo">
                    <p>1. 이름 : <b><?php echo htmlspecialchars($row['sname']); ?></b>
                        2. 학번 : <b><?php echo htmlspecialchars($row['sid']); ?></b>
                        3. 학과이름(전공): <b><?php echo htmlspecialchars($row['sdept']); ?></b></p>
                </div>
                <br>
                <table class="checkBox">
                    <colgroup>
                        <col width="400">
                        <col width="100">
                        <col width="100">
                        <col width="100">
                        <col width="100">
                        <col width="100">
                    </colgroup>
                    <tbody>
                        <tr>
                            <th>항목</th>
                            <th>매우그렇다</th>
                            <th>그렇다</th>
                            <th>보통이다</th>
                            <th>아니다</th>
                            <th>매우아니다</th>
                        </tr>
                        <tr>
                            <td>1. 나는 프로그래밍에 대해 자신이 있다.</td>
                            <td><input type="radio" id="poll01A" name="poll01" value="5" <?php if ($row['q1'] == 5)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll01B" name="poll01" value="4" <?php if ($row['q1'] == 4)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll01C" name="poll01" value="3" <?php if ($row['q1'] == 3)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll01D" name="poll01" value="2" <?php if ($row['q1'] == 2)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll01E" name="poll01" value="1" <?php if ($row['q1'] == 1)
                                echo 'checked'; ?>></td>
                        </tr>
                        <tr>
                            <td>2. 게임이 만들어지는 과정에 대해 이해가 있다.</td>
                            <td><input type="radio" id="poll02A" name="poll02" value="5" <?php if ($row['q2'] == 5)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll02B" name="poll02" value="4" <?php if ($row['q2'] == 4)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll02C" name="poll02" value="3" <?php if ($row['q2'] == 3)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll02D" name="poll02" value="2" <?php if ($row['q2'] == 2)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll02E" name="poll02" value="1" <?php if ($row['q2'] == 1)
                                echo 'checked'; ?>></td>
                        </tr>
                        <tr>
                            <td>3. 게임을 만들어 본 경험이 있다.</td>
                            <td><input type="radio" id="poll03A" name="poll03" value="5" <?php if ($row['q3'] == 5)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll03B" name="poll03" value="4" <?php if ($row['q3'] == 4)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll03C" name="poll03" value="3" <?php if ($row['q3'] == 3)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll03D" name="poll03" value="2" <?php if ($row['q3'] == 2)
                                echo 'checked'; ?>></td>
                            <td><input type="radio" id="poll03E" name="poll03" value="1" <?php if ($row['q3'] == 1)
                                echo 'checked'; ?>></td>
                        </tr>
                    </tbody>
                </table>
                <br>
                <p>1. 프로그래밍 동아리 가입 시 가장 중요하게 생각하는 부분은? (중복선택 가능)</p>
                <table class="pollTable">
                    <colgroup>
                        <col width="200">
                        <col width="200">
                        <col width="200">
                        <col width="200">
                    </colgroup>
                    <tbody>
                        <tr>
    <td><input type="checkbox" id="poll10A" name="poll10A" value="자료제공(컨텐츠)" 
        <?php if ($q4[0] == '1') echo 'checked'; ?>>자료제공(컨텐츠)</td>
    <td><input type="checkbox" id="poll10B" name="poll10B" value="스터디모임(자격증)" 
        <?php if ($q4[1] == '1') echo 'checked'; ?>>스터디 모임(자격증)</td>
    <td><input type="checkbox" id="poll10C" name="poll10C" value="커뮤니티" 
        <?php if ($q4[2] == '1') echo 'checked'; ?>>커뮤니티</td>
    <td><input type="checkbox" id="poll10D" name="poll10D" value="이벤트" 
        <?php if ($q4[3] == '1') echo 'checked'; ?>>이벤트</td>
</tr>
<tr>
    <td><input type="checkbox" id="poll10E" name="poll10E" value="게임만들기" 
        <?php if ($q4[4] == '1') echo 'checked'; ?>>게임 만들기</td>
    <td><input type="checkbox" id="poll10F" name="poll10F" value="공모전참여" 
        <?php if ($q4[5] == '1') echo 'checked'; ?>>공모전 참여</td>
    <td colspan="2"><input type="checkbox" id="poll10G" name="poll10G" value="기타의견 : " 
        <?php if (isset($q4[6]) && $q4[6] == '1') echo 'checked'; ?>>기타의견&nbsp;&nbsp;&nbsp;&nbsp;
        (<input type="text" id="poll10H" name="poll10H" class="underBarInput" value="<?php echo $q4a; ?>">)</td>
</tr>

                    </tbody>
                </table>

            </div>
            <br>
            <br>
            <br>
            <br>
            <div style="text-align: center;">
                <input type="hidden" name="sid" value="<?php echo htmlspecialchars($row['sid']); ?>">
                <input type="submit" value="수정">
                <p><b>위와 같이 내용을 수정합니다.</b></p>
            </div>
            <div class="Sinfo">
                <h1 style="text-align: center;">20213032_권영훈</h1>
            </div>

        </div>
    </form>
</body>

</html>