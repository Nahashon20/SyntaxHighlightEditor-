let name = prompt("Enter your name:");
let age = parseInt(prompt("Enter your age:"));

let currentYear = new Date().getFullYear();
let year100 = currentYear + (100 - age);

alert(`Hello, ${name}! You will turn 100 in the year ${year100}.`);
