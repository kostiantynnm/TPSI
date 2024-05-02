let firstNumber = null;
let secondNumber = null;
let result = null;

document.getElementById('firstNumber').addEventListener('click', function() {
	firstNumber = window.prompt('Enter first number');
});

document.getElementById('secondNumber').addEventListener('click', function() {
	secondNumber = window.prompt('Enter second number');
});

const playButton = document.getElementById('play-button');
const music = document.getElementById('music');

document.getElementById('calculate').addEventListener('click', function() {
    if(firstNumber != null && secondNumber != null){
        document.getElementById('image-container').innerHTML = '<img src="image.jpg" alt="Your Image">';
        document.getElementById('image-container').classList.add('show');
        if (music.paused) {
            music.play();
            playButton.textContent = 'Pause Music';
        } else {
            music.pause();
            playButton.textContent = 'Play Music';
        }
    }
    else{
        alert("Enter both of numbers first");
    }
});
