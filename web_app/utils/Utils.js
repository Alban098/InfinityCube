exports.rgbToHex = function(rgb) {
    let r = ((rgb >> 16) & 0xFF).toString(16);
    if (r.length < 2) r = '0' + r;
    let g = ((rgb >> 8) & 0xFF).toString(16);
    if (g.length < 2) g = '0' + g;
    let b = ((rgb) & 0xFF).toString(16);
    if (b.length < 2) b = '0' + b;
    return r + g + b;
}