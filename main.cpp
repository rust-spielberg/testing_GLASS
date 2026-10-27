const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

const bird = {
    x: 50,
    y: 200,
    width: 30,
    height: 30,
    gravity: 0.5,
    lift: -10,
    velocity: 0
};

const pipes = [];
const pipeGap = 150;
const pipeWidth = 50;
const pipeSpeed = 2;

function drawBird() {
    ctx.fillStyle = 'yellow';
    ctx.fillRect(bird.x, bird.y, bird.width, bird.height);
}

function drawPipes() {
    ctx.fillStyle = 'green';
    pipes.forEach(pipe => {
        ctx.fillRect(pipe.x, 0, pipeWidth, pipe.top);
        ctx.fillRect(pipe.x, canvas.height - pipe.bottom, pipeWidth, pipe.bottom);
    });
}

function updateBird() {
    bird.velocity += bird.gravity;
    bird.y += bird.velocity;

    if (bird.y + bird.height > canvas.height || bird.y < 0) {
        gameOver();
    }
}

function updatePipes() {
    pipes.forEach(pipe => {
        pipe.x -= pipeSpeed;

        if (pipe.x + pipeWidth < 0) {
            pipes.shift();
        }

        if (bird.x < pipe.x + pipeWidth &&
            bird.x + bird.width > pipe.x &&
            (bird.y < pipe.top || bird.y + bird.height > canvas.height - pipe.bottom)) {
            gameOver();
        }
    });
}

function gameOver() {
    alert('Game Over!');
    pipes.length = 0;
    bird.y = 200;
    bird.velocity = 0;
}

function addPipe() {
    const top = Math.random() * (canvas.height - pipeGap - 150) + 50;
    pipes.push({
        x: canvas.width,
        top: top,
        bottom: canvas.height - top - pipeGap
    });
}

function gameLoop() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawBird();
    drawPipes();
    updateBird();
    updatePipes();

    if (pipes.length === 0 || pipes[pipes.length - 1].x < canvas.width - 200) {
        addPipe();
    }

    requestAnimationFrame(gameLoop);
}

document.addEventListener('keydown', (e) => {
    if (e.code === 'Space') {
        bird.velocity = bird.lift;
    }
});

gameLoop();