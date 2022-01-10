$(function () {
    let options = {
        useHashPrefix: false,
        extensions: [
            {
                name: 'swatches', // extension name to load
                options: { // extension options
                    colors: {
                        'red': '#FF0000',
                        'green': '#00FF00',
                        'blue': '#0000FF',
                        'yellow': '#FFFF00',
                        'cyan': '#00FFFF',
                        'magenta': '#FF00FF',
                        'white': '#FFFFFF',
                        'gray': '#888888',
                        'black': '#000000',
                    },
                    namesAsValues: false
                }
            }
        ]
    }
    $('#primary').colorpicker(options).on('colorpickerHide', function (e) {$.getJSON(('/set?primary=' + e.value).replace('#', ''), function(data) {updateView(data)});});
    $('#secondary').colorpicker(options).on('colorpickerHide', function (e) { $.getJSON(('/set?secondary=' + e.value).replace('#', ''), function(data) {updateView(data)}); });
    $('#tertiary').colorpicker(options).on('colorpickerHide', function (e) { $.getJSON(('/set?tertiary=' + e.value).replace('#', ''), function(data) {updateView(data)}); });
});

function updateView(data) {
    selectPalette(data.palette);
    selectEffect(data.effect);
    $("#menu").css("box-shadow", "0 5px 20px 0px #" + rgbToHex(data.primary_color));
    $("#brightness").val(data.brightness);
    $("#intensity").val(data.intensity);
    $("#speed").val(data.speed);
    $('#primary').colorpicker('setValue', "#" + rgbToHex(data.primary_color));
    $('#secondary').colorpicker('setValue', "#" + rgbToHex(data.secondary_color));
    $('#tertiary').colorpicker('setValue', "#" + rgbToHex(data.tertiary_color));
    $('#palette-btn-0').css("background", "#" + rgbToHex(data.primary_color));
    $('#palette-btn-1').css("background", "linear-gradient(90deg, #" + rgbToHex(data.primary_color) + " 0%, #" + rgbToHex(data.secondary_color) + " 100%)");
    $('#palette-btn-2').css("background", "linear-gradient(90deg, #" + rgbToHex(data.primary_color) + " 0%, #" + rgbToHex(data.secondary_color) + " 50%, #" + rgbToHex(data.tertiary_color) + " 100%)");
}

function selectEffect(i) {
    $(".effect-btn").get().forEach(function(btn) {
        if ($(btn).attr('id') === 'effect-btn-' + i) {
            $(btn).addClass("btn-danger");
            $(btn).removeClass("btn-outline-danger");
        } else {
            $(btn).removeClass("btn-danger");
            $(btn).addClass("btn-outline-danger");
        }
    });
}

function selectPalette(i) {
    $(".palette-btn").get().forEach(function(btn) {
        if ($(btn).attr('id') === 'palette-btn-' + i) {
            $(btn).text("Selected");
        } else {
            $(btn).text("");
        }
    });
}

function rgbToHex(rgb) {
    let r = ((rgb >> 16) & 0xFF).toString(16);
    if (r.length < 2) r = '0' + r;
    let g = ((rgb >> 8) & 0xFF).toString(16);
    if (g.length < 2) g = '0' + g;
    let b = ((rgb) & 0xFF).toString(16);
    if (b.length < 2) b = '0' + b;
    return r + g + b;
}