JavaScript is a programming language that adds interactivity to your website (for example games,
responses when buttons are pressed or data is entered in forms, dynamic styling, and animation).
This article helps you get started with this exciting language and gives you an idea of what is
possible.

[What is JavaScript, really?](https://developer.mozilla.org/en-US/docs/Learn/Getting_started_with_the_web/JavaScript_basics)
===================
Because this article is only supposed to be a light introduction to JavaScript, we are not going to confuse you at this stage by talking in detail about what the difference is between the core JavaScript language and the different tools listed above. You can learn all that in detail later on, in our [JavaScript learning area](https://developer.mozilla.org/en-US/docs/Learn/JavaScript), and in the rest of MDN.

Below we will introduce you to some aspects of the core language, and you'll also play with a few browser API features too.

### A "Hello world!" example
  1. First, go to your test site and create a new folder named `scripts`. Then, within the new scripts folder you just created, create a new file called `main.js`. Save it in your scripts folder.
  2. Next, in your `index.html` file enter the following element on a new line just before the closing `</body>` tag:
``` html  
    <script src="scripts/main.js"></script>
```
  3. This is basically doing the same job as the `<link>` element for CSS — it applies the JavaScript
  to the page, so it can have an effect on the HTML (along with the CSS, and anything else on the
  page).
  4. Now add the following code to the `main.js` file:
``` js
    const myHeading = document.querySelector('h1');
    myHeading.textContent = 'Hello world!';
```
  5. Finally, make sure the HTML and JavaScript files are saved, then load `index.html` in the browser.

#### What happened?
using a function called `querySelector()` to grab a reference to your heading, and store it in a variable called 
`myHeading`. This is very similar to what we did using CSS selectors. When you want to do something to an element, 
you need to select it first.

After that, you set the value of the `myHeading` variable's `textContent` property (which represents the content of the heading) to "Hello world!".

### Language basics crash course
#### Variables
Variables are containers that you can store values in. You start by declaring a variable
    with the `var` (less recommended, dive deeper for the explaination) or the `let` keyword,
    followed by any name you want to call it ...

#### Comments
Comments are, essentially, short snippets of text that can be added in-between code which
    is ignored by the browser. You can put comments into JavaScript code, just as you can in CSS:

#### Operators
An operator is a mathematical symbol which produces a result based on two values (or
    variables).

#### Conditionals
Conditionals are code structures which allow you to test if an expression returns true or
    not, running alternative code revealed by its result. A very common form of conditionals
    is the `if ... else` statement. For example:

``` js
    let iceCream = 'chocolate';
    if(iceCream === 'chocolate') {
      alert('Yay, I love chocolate ice cream!');
    } else {
      alert('Awwww, but chocolate is my favorite...');
    }
```

#### Functions
Functions are a way of packaging functionality that you wish to reuse. When you need the
    procedure you can call a function, with the function name, instead of rewriting the entire
    code each time. You have already seen some uses of functions above, for example:

``` js
    let myVariable = document.querySelector('h1');  
```
``` js
    alert('hello!');
```
These functions, `document.querySelector` and `alert`, are built into the browser for you to
    use whenever you desire.

If you see something which looks like a variable name, but has parentheses — `()` — after
    it, it is likely a function. Functions often take arguments — bits of data they need to
    do their job. These go inside the parentheses, separated by commas if there is more than one
    argument.

The good news is you can define your own functions — in this next example we write a simple
    function which takes two numbers as arguments and multiplies them:
``` js
      function multiply(num1,num2) {
        let result = num1 * num2;
        return result;
      }
```

#### Events
Real interactivity on a website needs events. These are code structures which listen for
    things happening in the browser and runs code in response. The most obvious example is
    the `click event`, which is fired by the browser when you click on something with your mouse.
    To demonstrate this, enter the following into your console, then click on the current webpage:
``` js
        document.querySelector('html').onclick = function() {
            alert('Ouch! Stop poking me!');
        } 
```
There are many ways to attach an event to an element. Here we select the `<html>` element,
    setting its `onclick` handler property equal to an anonymous (i.e. nameless) function,
    which contains the code we want the click event to run.

Note that
``` js
    document.querySelector('html').onclick = function() {};
```
is equivalent to
```js
    let myHTML = document.querySelector('html');
    myHTML.onclick = function() {}; 
```
It's just shorter.

#### Adding an image changer
In this section, we'll add an additional image to our site using some more DOM API features,
    using some JavaScript to switch between the two when the image is clicked.
``` js
    let myImage = document.querySelector('img');

    myImage.onclick = function() {
        let mySrc = myImage.getAttribute('src');
        if(mySrc === 'images/firefox-icon.png') {
          myImage.setAttribute ('src','images/firefox2.png');
        } else {
          myImage.setAttribute ('src','images/firefox-icon.png');
        }
    } 
```
You store a reference to your `<img>` element in the `myImage` variable. Next, you make
    this variable's `onclick` event handler property equal to a function with no name (an
    "anonymous" function). Now, every time this element is clicked:

1. You retrieve the value of the image's src attribute.
2. You use a conditional to check whether the src value is equal to the path to the
original image:
    1. If it is, you change the src value to the path to the 2nd image, forcing the other
    image to be loaded inside the `<img>` element.
    2. If it isn't (meaning it must already have changed), the src value swaps back to
    the original image path, to the original state.

#### Adding a personalized welcome message
Next we will add another bit of code, changing the page's title to a personalized welcome
    message when the user first navigates to the site. This welcome message will persist, should
    the user leave the site and later return — we will save it using the `Web Storage API`. We will
    also include an option to change the user and, therefore, the welcome message anytime it is
    required.

1. In index.html, add the following line just before the `<script>` element:
```   <button>Change user</button>```
2. In `main.js`, place the following code at the bottom of the file, exactly as written — this
    takes references to the new button and the heading, storing them inside variables:
``` js
    let myButton = document.querySelector('button');
    let myHeading = document.querySelector('h1'); 
```
3. Now add the following function to set the personalized greeting — this won't do anything
    yet, but we'll fix this in a moment:
``` js
    function setUserName() {
      let myName = prompt('Please enter your name.');
      localStorage.setItem('name', myName);
      myHeading.textContent = 'Mozilla is cool, ' + myName;
    }
```
This function contains a `prompt()` function, which brings up a dialog box, a bit like
    `alert()`. This `prompt()`, however, asks the user to enter some data, storing it in a variable
    after the user presses **OK**. In this case, we are asking the user to enter their name. Next,
    we call on an API called `localStorage`, which allows us to store data in the browser and later
    retrieve it. We use localStorage's `setItem()` function to create and store a data item called
    `'name'`, setting its value to the `myName` variable which contains the data the user entered.
    Finally, we set the `textContent` of the heading to a string, plus the user's newly stored name.
    
4. Next, add this `if ... else` block — we could call this the initialization code, as it
    structures the app when it first loads:
``` js
    if(!localStorage.getItem('name')) {
      setUserName();
    } else {
      let storedName = localStorage.getItem('name');
      myHeading.textContent = 'Mozilla is cool, ' + storedName;
    }
```
This block first uses the negation operator (logical NOT, represented by the !) to check whether
    the `name` data exists. If not, the `setUserName()` function is run to create it. If it exists
    (that is, the user set it during a previous visit), we retrieve the stored name using `getItem()`
    and set the `textContent` of the heading to a string, plus the user's name, as we did inside
    `setUserName()`.
    
5. Finally, put the below `onclick` event handler on the button. When clicked, the `setUserName()`
    function is run. This allows the user to set a new name, when they wish, by pressing the button:
``` js
    myButton.onclick = function() {
      setUserName();
    } 
```
Now when you first visit the site, it will ask you for your username, then give you a
    personalized message. You can change the name any time you like by pressing the button. As an
    added bonus, because the name is stored inside localStorage, it persists after the site is closed
    down, keeping the personalized message there when you next open the site!

#### A user name of null?
When you run the example and get the dialog box that prompts you to enter your user name, try
    pressing the Cancel button. You should end up with a title that reads "Mozilla is cool, null".
    This is because when you cancel the prompt, the value is set as `null`, a special value in
    JavaScript that basically refers to the absence of a value.
If you wanted to avoid these problems, you could check that the user hasn't entered `null` or
    a blank name by updating you `setUserName()` function to this:
``` js
    function setUserName() {
      let myName = prompt('Please enter your name.');
      if(!myName || myName === null) {
        setUserName();
      } else {
        localStorage.setItem('name', myName);
        myHeading.innerHTML = 'Mozilla is cool, ' + myName;
      }
    } 
```
In human language — if `myName` has no value, or its value is `null`, run `setUserName()`
    again from the start. If it does have a value (if the above statements are not true), then
    store the value in `localStorage` and set it as the heading's text.

### Conclusion
If you have followed all the instructions in this article, you should end up with a page that looks something 
like this (you can also [view our version here](https://mdn.github.io/beginner-html-site-scripted/)):


---
#### learningJS html
``` html
<!-- learningJS.html 201912 -->
<!DOCTYPE html>
<html>
<body>

    <h2>Kick start JavaScript</h2>

    <p>This example calls a function which performs a calculation, and returns the result:</p>
    <p id="demo"></p>

    <script>
        function myFunction(p1, p2) {
          return p1 * p2;
        }
        document.getElementById("demo").innerHTML = myFunction(4, 3);
    </script>

    <script>
        //document.getElementById("demo").innerHTML ="The temperature is " + toCelsius(77) + " Celsius";

        function toCelsius(fahrenheit) {
          return (5/9) * (fahrenheit-32);
        }

        var myText = "The temperature is " + toCelsius(77) + " Celsius";
    </script>


    <p>These onclicks demonstrate three output types:</p>
    <button type="button" onclick='document.getElementById("demo").innerHTML = myText'>Click Me!</button>
    <button type="button" onclick=alert(myText)>Click Alert!</button>
    <button type="button" onclick=console.log(myText)>Concole Log</button>

    <script>
        var x1 = {};    // x1: object
        var x2 = "";    // x2: string
        var x3 = 0;     // x3: number
        var x4 = false; // x4: boolean
        var x5 = [];    // x5: object
        var x6 = /()/;  // x6: object
        var x7 = function(){};  // x7: function
    </script>

    <p>jQuery Basic syntax is: $(selector).action() <br>
        example: clicks on any <%p%> elements, it will be hidden:</p>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script>
        $(document).ready(function(){
          $("p").click(function(){
            $(this).hide();
          });
        });
    </script>
    <!--
    jQuery Event Methods
    Here are some common DOM events:
    Mouse Events	Keyboard Events	Form Events	Document/Window Events
    click	keypress	submit	load
    dblclick	keydown	change	resize
    mouseenter	keyup	focus	scroll
    mouseleave	 	blur	unload
    https://www.w3schools.com/jquery/jquery_events.asp
    -->


    <h3>HTML DOM querySelector() Method</h3>
    <h4 class="example">A heading with class="example"</h4>
    <p class="example">A paragraph with class="example".</p>

    <p>Click the button to add a background color to the first element in the document with class="example".</p>

    <button onclick="myFunction()">Try it</button>

    <script>
    function myFunction() {
      document.querySelector(".example").style.backgroundColor = "red";
    }
    </script>


    <h2>JavaScript Object Constructors</h2>

    <p id="demo3"></p>

    <script>

    // Constructor function for Person objects
    function Person(first, last, age, eye) {
      this.firstName = first;
      this.lastName = last;
      this.age = age;
      this.eyeColor = eye;
    }

    // Create 2 Person objects
    var myFather = new Person("John", "Doe", 50, "blue");
    var myMother = new Person("Sally", "Rally", 48, "green");

    // Add a name method to first object
    myFather.name = function() {
      return this.firstName + " " + this.lastName;
    };

    // Display full name
    document.getElementById("demo3").innerHTML =
    "My father is " + myFather.name();
    </script>

  <script>
    function factorial(n) {
      if (n == 0) {
        return 1;
      } else {
        return factorial(n - 1) * n;
      }
    }
  </script>


</body>
</html>
```
