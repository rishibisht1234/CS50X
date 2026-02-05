document.addEventListener('DOMContentLoaded', () => {
    const avatar = document.querySelector('.avatar');
    if (!avatar) return;

    let state = 0;

    avatar.addEventListener('click', () => {
        const rect = avatar.getBoundingClientRect();
        const x = rect.left + rect.width / 2;
        const y = rect.top + rect.height / 2;

        const ripple = document.createElement('div');
        ripple.classList.add('ripple');

        if (state === 0) {
            ripple.classList.add('green');
            document.body.classList.remove('blue');
            document.body.classList.add('green');
            state = 1;
        } else {
            ripple.classList.add('blue');
            document.body.classList.remove('green');
            document.body.classList.add('blue');
            state = 0;
        }

        ripple.style.left = `${x}px`;
        ripple.style.top = `${y}px`;
        document.body.appendChild(ripple);

        // Remove ripple after animation
        ripple.addEventListener('animationend', () => {
            ripple.remove();
        });
    });
});
