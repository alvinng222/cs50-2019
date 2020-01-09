``` html
<!DOCTYPE html>

<html lang="en">
    <head>

        <!-- Required meta tags -->
        <meta charset="utf-8"/>
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

        <!-- Bootstrap CSS -->
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">

        <link href="/static/less/styles.css" rel="stylesheet">

        <title>Similarities</title>

    </head>
    <body>

        <nav class="navbar navbar-expand fixed-top navbar-dark bg-dark">
            <a class="navbar-brand" href="/">Similarities</a>
            <ul class="navbar-nav">
                <li class="nav-item active">
                    <a class="nav-link" href="/less">less <span class="sr-only">(current)</span></a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/more">more</a>
                </li>
            </ul>
        </nav>

        <div class="container-fluid">
            <div class="row">
                
<div class="col">
    <form action="/less/compare" enctype="multipart/form-data" method="post">
        <div class="form-group">
            <input class="form-control-file" name="file1" type="file">
        </div>
        <div class="form-group">
            <input class="form-control-file" name="file2" type="file">
        </div>
        <div class="form-group">
            <div class="form-check">
                <label class="form-check-label">
                    <input class="form-check-input" name="algorithm" type="radio" value="lines">
                    Compare lines
                </label>
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input class="form-check-input" name="algorithm" type="radio" value="sentences">
                    Compare sentences
                </label>
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input class="form-check-input" name="algorithm" type="radio" value="substrings">
                    Compare substrings
                    <input class="form-control form-control-sm" min="1" name="length" placeholder="of length n" type="number">
                </label>
            </div>
        </div>
        <button class="btn btn-primary" type="submit">Compare</button>
    </form>
</div>

            </div>
        </div>

        <!-- Optional JavaScript -->
        <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>

        <script src="/static/less/scripts.js"></script>

    </body>
</html>
```
