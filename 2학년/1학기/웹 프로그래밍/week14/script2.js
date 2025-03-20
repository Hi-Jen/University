function typeWriter(element, lines, delay = 100, lineDelay = 500) {
    let lineIndex = 0;
    let charIndex = 0;

    function addLetter() {
        if (lineIndex < lines.length) {
            if (charIndex < lines[lineIndex].length) {
                element.innerHTML += lines[lineIndex].charAt(charIndex);
                charIndex++;
                setTimeout(addLetter, delay);
            } else {
                element.innerHTML += '\n';
                charIndex = 0;
                lineIndex++;
                setTimeout(addLetter, lineDelay);
            }
        }
    }
    addLetter();
}

function convertToBinary() {
    const input1 = parseInt(document.getElementById('input1').value);
    const input2 = parseInt(document.getElementById('input2').value);
    const conversionText = document.getElementById('conversionText');
    conversionText.innerHTML = '';

    if (isNaN(input1) || isNaN(input2)) {
        typeWriter(conversionText, ['유효한 숫자를 입력하세요.']);
        return;
    }

    const binaryInput1 = toBinaryWithSign(input1);
    const binaryInput2 = toBinaryWithSign(input2);

    document.getElementById('binaryInput1').innerText = binaryInput1;
    document.getElementById('binaryInput2').innerText = binaryInput2;

    const steps1 = convertStepsToBinary(input1);
    const steps2 = convertStepsToBinary(input2);

    const conversionDetails = [
        `입력1 (${input1}) -> 2진수: ${binaryInput1}`,
        `입력2 (${input2}) -> 2진수: ${binaryInput2}`,
        `\n입력값1:\n`,
        ...steps1,
        `\n입력값2:\n`,
        ...steps2
    ];
    typeWriter(conversionText, conversionDetails, 50, 500);
}

function convertStepsToBinary(number) {
    const steps = [];
    let n = Math.abs(number);
    while (n > 0) {
        const remainder = n % 2;
        steps.push(`${n} ÷ 2 = ${Math.floor(n / 2)} ... ${remainder}`);
        n = Math.floor(n / 2);
    }
    return steps;
}

function toBinaryWithSign(number) {
    const BITS = 10;
    let binary = Math.abs(number).toString(2).padStart(BITS, '0');
    if (number < 0) {
        binary = (parseInt(binary, 2) ^ ((1 << BITS) - 1)).toString(2).padStart(BITS, '0');
        binary = (parseInt(binary, 2) + 1).toString(2).padStart(BITS, '0');
    }
    return binary;
}

function addBinary() {
    const binaryInput1 = document.getElementById('binaryInput1').innerText;
    const binaryInput2 = document.getElementById('binaryInput2').innerText;
    const binaryResult = document.getElementById('binaryResult');
    const carryBorrow = document.getElementById('carryBorrow');
    binaryResult.innerHTML = '';
    carryBorrow.innerHTML = '';

    if (!binaryInput1 || !binaryInput2) {
        alert('먼저 입력값을 2진수로 변환하세요.');
        return;
    }

    const maxLength = Math.max(binaryInput1.length, binaryInput2.length);
    const bin1 = binaryInput1.padStart(maxLength, '0');
    const bin2 = binaryInput2.padStart(maxLength, '0');

    let carry = 0;
    let result = '';
    let steps = [];
    let carrySteps = [];

    for (let i = maxLength - 1; i >= 0; i--) {
        const sum = parseInt(bin1[i], 2) + parseInt(bin2[i], 2) + carry;
        carry = sum >> 1;
        result = (sum & 1) + result;
        steps.push(`비트 ${i}: ${bin1[i]} + ${bin2[i]} + 캐리 ${carry} = ${sum & 1} (새 캐리: ${carry})`);
        carrySteps.push(`캐리 ${i}: ${carry}`);
    }

    if (carry) {
        result = carry + result;
        steps.push(`최종 캐리: ${carry}`);
        carrySteps.push(`최종 캐리: ${carry}`);
    }

    // Determine if the result should be negative by examining the overflow
    const isNegativeResult = (result.length > maxLength) ? (result[0] === '1') : (result[maxLength - 1] === '1');
    if (isNegativeResult) {
        result = result.slice(-maxLength); // Truncate to the original bit length
    }

    typeWriter(binaryResult, [result.slice(-maxLength)], 50, 500);
    typeWriter(carryBorrow, carrySteps, 50, 500);
    document.getElementById('binaryResultString').innerText = result.slice(-maxLength);
}

function convertToDecimal() {
    const binaryResult = document.getElementById('binaryResultString').innerText;
    const decimalResult = document.getElementById('decimalResult');
    decimalResult.innerHTML = '';

    if (!binaryResult) {
        alert('먼저 2진수 덧셈을 수행하세요.');
        return;
    }

    const isNegative = binaryResult[0] === '1';
    let decimalNumber;

    if (isNegative) {
        decimalNumber = -(parseInt(binaryResult, 2) ^ ((1 << binaryResult.length) - 1)) - 1;
    } else {
        decimalNumber = parseInt(binaryResult, 2);
    }

    typeWriter(decimalResult, [`10진수 결과: ${decimalNumber}`], 50, 500);
}
