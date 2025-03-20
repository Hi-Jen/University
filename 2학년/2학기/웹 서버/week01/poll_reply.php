<?php
// 설문지 데이터 출력

// 이름, 학번, 학과이름(전공)
echo '1. 이름: ' . $_POST['sname'] . "<br/>";
echo '2. 학번: ' . $_POST['snum'] . "<br/>";
echo '3. 학과이름(전공): ' . $_POST['sdept'] . "<br/><br/>";

// 라디오 버튼 질문 응답
echo '1. 나는 프로그래밍에 대해 자신이 있다: ' . $_POST['poll01'] . "<br/>";
echo '2. 게임이 만들어지는 과정에 대해 이해가 있다: ' . $_POST['poll02'] . "<br/>";
echo '3. 게임을 만들어 본 경험이 있다: ' . $_POST['poll03'] . "<br/><br/>";

// 프로그래밍 동아리 가입 시 중요하게 생각하는 부분 (체크박스)
echo '1. 프로그래밍 동아리 가입 시 가장 중요하게 생각하는 부분은? (중복 선택 가능): ';
echo $_POST['poll10A'] . ' ';
echo $_POST['poll10B'] . ' ';
echo $_POST['poll10C'] . ' ';
echo $_POST['poll10D'] . ' ';
echo $_POST['poll10E'] . ' ';
echo $_POST['poll10F'] . ' ';
echo $_POST['poll10G'] . ' ';
echo "<br/><br/>";

// 다룰 수 있는 프로그래밍 언어 (체크박스)
echo '2. 자신이 다룰 수 있는 프로그래밍 언어는? (중복선택 가능): ';
echo $_POST['poll20A'] . ' ';
echo $_POST['poll20B'] . ' ';
echo $_POST['poll20C'] . ' ';
echo $_POST['poll20D'] . ' ';
echo "<br/><br/>";

// 만들고 싶은 게임/ 선호하는 게임의 종류 (체크박스)
echo '3. 만들고 싶은 게임/ 선호하는 게임의 종류를 선택하여 주세요. (중복선택 가능): ';
echo $_POST['poll30A'] . ' ';
echo $_POST['poll30B'] . ' ';
echo $_POST['poll30C'] . ' ';
echo $_POST['poll30D'] . ' ';
echo "<br/><br/>";

// 이해하고 있는/ 다룰 수 있는 게임 엔진 (체크박스)
echo '4. 이해하고 있는/다룰 수 있는 게임 엔진: ';
echo ($_POST['poll40A'] ? '유니티, ' : '') . ($_POST['poll40B'] ? '인리얼, ' : '');
echo ($_POST['poll40C'] ? '소스 엔진, ' : '') . ($_POST['poll40D'] ? '주피터, ' : '');
echo ($_POST['poll40E'] ? '기타: ' . $_POST['poll40F'] : '') . "<br/><br/>";

// 같은 팀 희망 멤버 및 희망하는 멘토
$poll50 = $_POST['poll50'];
$poll60 = $_POST['poll60'];

echo '같은 팀 희망 멤버: ' . $poll50 . "<br/>";
echo '희망하는 멘토: ' . $poll60 . "<br/><br/>";

echo '<p>20213032 권영훈</p>';
?>
