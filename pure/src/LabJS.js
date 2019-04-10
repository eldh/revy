const { pow } = Math
const LAB_CONSTANTS = {
  kn: 18,
  xn: 0.95047,
  yn: 1,
  zn: 1.08883,
  t0: 0.137931034,
  t1: 0.206896552,
  t2: 0.12841855,
  t3: 0.008856452,
}

export const rgb2lab = (r, g, b) => {
  const [x, y, z] = rgb2xyz(r, g, b)
  const l = 116 * y - 16
  return [l < 0 ? 0 : l, 500 * (x - y), 200 * (y - z)]
}

const rgb_xyz = r => {
  if ((r /= 255) <= 0.04045) return r / 12.92
  return pow((r + 0.055) / 1.055, 2.4)
}

const xyz_lab = t => {
  if (t > LAB_CONSTANTS.t3) return pow(t, 1 / 3)
  return t / LAB_CONSTANTS.t2 + LAB_CONSTANTS.t0
}

export const rgb2xyz = (r, g, b) => {
  r = rgb_xyz(r)
  g = rgb_xyz(g)
  b = rgb_xyz(b)
  console.log('r,g,b', r, g, b)

  const x = xyz_lab((0.4124564 * r + 0.3575761 * g + 0.1804375 * b) / LAB_CONSTANTS.xn)
  const y = xyz_lab((0.2126729 * r + 0.7151522 * g + 0.072175 * b) / LAB_CONSTANTS.yn)
  const z = xyz_lab((0.0193339 * r + 0.119192 * g + 0.9503041 * b) / LAB_CONSTANTS.zn)
  return [x, y, z]
}

export const lab2rgb = (l, a, b) => {
  let x, y, z, r, g, b_

  y = (l + 16) / 116
  x = isNaN(a) ? y : y + a / 500
  z = isNaN(b) ? y : y - b / 200

  y = LAB_CONSTANTS.yn * lab_xyz(y)
  x = LAB_CONSTANTS.xn * lab_xyz(x)
  z = LAB_CONSTANTS.zn * lab_xyz(z)

  console.log('x,y,z', x, y, z)
  r = xyz_rgb(3.2404542 * x - 1.5371385 * y - 0.4985314 * z) // D65 -> sRGB
  console.log('r', r)

  g = xyz_rgb(-0.969266 * x + 1.8760108 * y + 0.041556 * z)
  b_ = xyz_rgb(0.0556434 * x - 0.2040259 * y + 1.0572252 * z)

  return [r, g, b_]
}

const xyz_rgb = r => {
  return 255 * (r <= 0.00304 ? 12.92 * r : 1.055 * pow(r, 1 / 2.4) - 0.055)
}

const lab_xyz = t => {
  return t > LAB_CONSTANTS.t1 ? t * t * t : LAB_CONSTANTS.t2 * (t - LAB_CONSTANTS.t0)
}
