<form method="POST" action="./insertReply.php"> <!--action="/action_page.php"-->
    <label for="sname">1. 이름:</label>
    <input type="text" name="sname">
    <label for="snum">1. 학번:</label>
    <input type="text" name="snum">
    <label for="sdept">1. 학과이름(전공):</label>
    <input type="text" name="sdept"><br><br>

    <table>
        <colgroup>
            <col width=400>
            <col width=100>
            <col width=100>
            <col width=100>
            <col width=100>
            <col width=100>
        </colgroup>

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
            <td align="center"><input type="radio" name="poll01" value="5"></td>
            <td align="center"><input type="radio" name="poll01" value="4"></td>
            <td align="center"><input type="radio" name="poll01" value="3"></td>
            <td align="center"><input type="radio" name="poll01" value="2"></td>
            <td align="center"><input type="radio" name="poll01" value="1"></td>
        </tr>
        <tr>
            <td>2. 게임이 만들어 지는 과정에 대해 이해가 있다.</td>
            <td align="center"><input type="radio" name="poll02" value="5"></td>
            <td align="center"><input type="radio" name="poll02" value="4"></td>
            <td align="center"><input type="radio" name="poll02" value="3"></td>
            <td align="center"><input type="radio" name="poll02" value="2"></td>
            <td align="center"><input type="radio" name="poll02" value="1"></td>
        </tr>
        <tr>
            <td>3. 게임을 만들어 본 경험이 있다.</td>
            <td align="center"><input type="radio" name="poll03" value="5"></td>
            <td align="center"><input type="radio" name="poll03" value="4"></td>
            <td align="center"><input type="radio" name="poll03" value="3"></td>
            <td align="center"><input type="radio" name="poll03" value="2"></td>
            <td align="center"><input type="radio" name="poll03" value="1"></td>
        </tr>
    </table><br />
    <p>1. 프로그래밍 동아리 가입 시 가장 중요하게 생각하는 부분은? (중복선택 가능)</p>
    <table class=pollTable>
        <colgroup>
            <col width=200>
            <col width=200>
            <col width=200>
            <col width=200>
        </colgroup>
        <tr>
            <td><input type="checkbox" name="poll10A" value="poll10A">
                <label for="poll01A">자료제공(콘텐츠)</label>
            </td>
            <td><input type="checkbox" name="poll10B" value="poll10B">
                <label for="poll01B">스터디모임(자격증)</label>
            </td>
            <td><input type="checkbox" name="poll10C" value="poll10C">
                <label for="poll01C">커뮤니티</label>
            </td>
            <td><input type="checkbox" name="poll10D" value="poll10D">
                <label for="poll01D">이벤트</label>
            </td>
        </tr>
        <tr>
            <td><input type="checkbox" name="poll10E" value="poll10E">
                <label for="poll10E">게임 만들기</label>
            </td>
            <td><input type="checkbox" name="poll10F" value="poll10F">
                <label for="poll10F">공모전 참여</label>
            </td>
            <td colspan=2><input type="checkbox" name="poll10G" value="G">
                <label for="poll10G">기타의견</label>&nbsp;&nbsp;&nbsp;&nbsp;
                (<input type="text" name="poll10H">)
            </td>
        </tr>
    </table>

    <br /><br /><input style="margin: auto; display:block;" type="submit" value="확인">

</form>