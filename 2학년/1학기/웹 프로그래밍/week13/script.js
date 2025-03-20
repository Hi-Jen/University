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
                element.innerHTML += '<br>';
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
        `입력값1:`,
        ...steps1,
        `입력값2:`,
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
    return steps.length ? steps : ["0"];
}

function toBinaryWithSign(number) {
    const BITS = 10;
    let binary = Math.abs(number).toString(2).padStart(BITS - 1, '0');
    if (number < 0) {
        binary = '1' + binary;
    } else {
        binary = '0' + binary;
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

    const sign1 = binaryInput1[0];
    const sign2 = binaryInput2[0];
    const mag1 = binaryInput1.slice(1);
    const mag2 = binaryInput2.slice(1);

    const int1 = parseInt(mag1, 2) * (sign1 === '1' ? -1 : 1);
    const int2 = parseInt(mag2, 2) * (sign2 === '1' ? -1 : 1);

    const sum = int1 + int2;

    const resultBinary = toBinaryWithSign(sum);

    const result = resultBinary.padStart(binaryInput1.length, '0');

    // Calculate carries for each bit
    const carries = calculateCarries(binaryInput1.slice(1), binaryInput2.slice(1));

    typeWriter(binaryResult, [result], 50, 500);
    typeWriter(carryBorrow, carries, 50, 500);
    document.getElementById('binaryResultString').innerText = result;
}

function calculateCarries(bin1, bin2) {
    let carry = 0;
    const carries = [];
    for (let i = bin1.length - 1; i >= 0; i--) {
        const sum = parseInt(bin1[i]) + parseInt(bin2[i]) + carry;
        carry = sum > 1 ? 1 : 0;
        carries.unshift(`캐리${bin1.length - i}: ${carry}`);
    }
    return carries;
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
    let decimalNumber = parseInt(binaryResult.slice(1), 2);
    if (isNegative) {
        decimalNumber = -decimalNumber;
    }

    typeWriter(decimalResult, [`10진수 결과: ${decimalNumber}`], 50, 500);
}

