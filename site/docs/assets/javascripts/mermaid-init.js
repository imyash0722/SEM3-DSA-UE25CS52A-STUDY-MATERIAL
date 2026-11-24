/**
 * Theme-aware Mermaid Initialization and Dynamic Dark Mode Contrast Sync
 */
(function() {
  function getTheme() {
    const scheme = document.body ? document.body.getAttribute('data-md-color-scheme') : 'default';
    return scheme === 'slate' ? 'dark' : 'default';
  }

  function parseRgb(color) {
    if (!color) return null;
    const match = color.match(/rgba?\((\d+),\s*(\d+),\s*(\d+)/i);
    if (match) return [parseInt(match[1]), parseInt(match[2]), parseInt(match[3])];
    if (color.startsWith('#')) {
      let hex = color.slice(1);
      if (hex.length === 3) hex = hex.split('').map(c => c + c).join('');
      if (hex.length === 6) {
        return [parseInt(hex.slice(0, 2), 16), parseInt(hex.slice(2, 4), 16), parseInt(hex.slice(4, 6), 16)];
      }
    }
    return null;
  }

  function getLuminance(r, g, b) {
    const a = [r, g, b].map(v => {
      v /= 255;
      return v <= 0.03928 ? v / 12.92 : Math.pow((v + 0.055) / 1.055, 2.4);
    });
    return a[0] * 0.2126 + a[1] * 0.7152 + a[2] * 0.0722;
  }

  function adaptSvgNodes() {
    const isDark = document.body && document.body.getAttribute('data-md-color-scheme') === 'slate';
    const svgs = document.querySelectorAll('.mermaid svg, svg[id^="mermaid-"]');

    svgs.forEach(function(svg) {
      const nodes = svg.querySelectorAll('.node');
      nodes.forEach(function(node) {
        const shapes = node.querySelectorAll('rect, circle, polygon, ellipse, path');
        const labels = node.querySelectorAll('.nodeLabel, text, span');
        const nodeClass = (node.getAttribute('class') || '') + ' ' + (node.id || '');

        shapes.forEach(function(shape) {
          if (!shape.hasAttribute('data-orig-style')) {
            shape.setAttribute('data-orig-style', shape.getAttribute('style') || '');
          }
          const origStyle = shape.getAttribute('data-orig-style');

          if (isDark) {
            let handled = false;

            // 1. Explicit classes or named styles
            if (nodeClass.includes('rootNode')) {
              shape.style.setProperty('fill', '#4a2c00', 'important');
              shape.style.setProperty('stroke', '#ffb74d', 'important');
              handled = true;
            } else if (nodeClass.includes('lessThan')) {
              shape.style.setProperty('fill', '#1b5e20', 'important');
              shape.style.setProperty('stroke', '#81c784', 'important');
              handled = true;
            } else if (nodeClass.includes('greaterThan')) {
              shape.style.setProperty('fill', '#1a237e', 'important');
              shape.style.setProperty('stroke', '#64b5f6', 'important');
              handled = true;
            }

            // 2. Inline style regex match
            if (!handled && origStyle) {
              if (/fill:\s*(#fff3e0|#fff8e1|#ffe0b2|rgb\(255,\s*243,\s*224\))/i.test(origStyle)) {
                shape.style.setProperty('fill', '#4a2c00', 'important');
                shape.style.setProperty('stroke', '#ffb74d', 'important');
                handled = true;
              } else if (/fill:\s*(#e8f5e9|#c8e6c9|#dcedc8|rgb\(232,\s*245,\s*233\)|rgb\(200,\s*230,\s*201\))/i.test(origStyle)) {
                shape.style.setProperty('fill', '#1b5e20', 'important');
                shape.style.setProperty('stroke', '#81c784', 'important');
                handled = true;
              } else if (/fill:\s*(#ffebee|#ffcdd2|#fce4ec|rgb\(255,\s*235,\s*238\)|rgb\(255,\s*205,\s*210\))/i.test(origStyle)) {
                shape.style.setProperty('fill', '#5c1d1d', 'important');
                shape.style.setProperty('stroke', '#ef5350', 'important');
                handled = true;
              } else if (/fill:\s*(#e3f2fd|#e1f5fe|#bbf|rgb\(227,\s*242,\s*253\))/i.test(origStyle)) {
                shape.style.setProperty('fill', '#1a237e', 'important');
                shape.style.setProperty('stroke', '#64b5f6', 'important');
                handled = true;
              } else if (/fill:\s*(#f3e5f5|#f9f|rgb\(243,\s*229,\s*245\))/i.test(origStyle)) {
                shape.style.setProperty('fill', '#4a148c', 'important');
                shape.style.setProperty('stroke', '#ce93d8', 'important');
                handled = true;
              } else if (/fill:\s*(#f96)/i.test(origStyle)) {
                shape.style.setProperty('fill', '#5d2e00', 'important');
                shape.style.setProperty('stroke', '#ff9800', 'important');
                handled = true;
              }
            }

            // 3. Computed fill check for any unhandled light colors (e.g. cylinder #ececff or classDefs)
            if (!handled) {
              const comp = window.getComputedStyle(shape);
              const rgb = parseRgb(comp.fill);
              if (rgb) {
                const lum = getLuminance(rgb[0], rgb[1], rgb[2]);
                if (lum > 0.35) {
                  // Light background in dark mode -> adapt semantically
                  if (rgb[0] > rgb[2] + 20 && rgb[1] > rgb[2] + 20) {
                    // Warm amber / yellow
                    shape.style.setProperty('fill', '#4a2c00', 'important');
                    shape.style.setProperty('stroke', '#ffb74d', 'important');
                  } else if (rgb[1] > rgb[0] && rgb[1] > rgb[2]) {
                    // Green
                    shape.style.setProperty('fill', '#1b5e20', 'important');
                    shape.style.setProperty('stroke', '#81c784', 'important');
                  } else if (rgb[0] > rgb[1] + 20 && rgb[0] > rgb[2] + 20) {
                    // Red / Pink
                    shape.style.setProperty('fill', '#5c1d1d', 'important');
                    shape.style.setProperty('stroke', '#ef5350', 'important');
                  } else if (rgb[0] > 180 && rgb[1] < 160 && rgb[2] > 180) {
                    // Purple
                    shape.style.setProperty('fill', '#4a148c', 'important');
                    shape.style.setProperty('stroke', '#ce93d8', 'important');
                  } else {
                    // Blue / lavender / unstyled default
                    shape.style.setProperty('fill', '#1a237e', 'important');
                    shape.style.setProperty('stroke', '#64b5f6', 'important');
                  }
                }
              }
            }

            labels.forEach(function(l) {
              l.style.setProperty('color', '#f0f0f0', 'important');
              l.style.setProperty('fill', '#f0f0f0', 'important');
            });
          } else {
            // Light Mode: Restore original inline styles
            shape.setAttribute('style', origStyle);
            labels.forEach(function(l) {
              l.style.removeProperty('color');
              l.style.removeProperty('fill');
            });
          }
        });
      });
    });
  }

  function initMermaid() {
    if (typeof mermaid === 'undefined') return;

    mermaid.initialize({
      startOnLoad: true,
      theme: getTheme(),
      securityLevel: 'loose',
      flowchart: {
        useMaxWidth: true,
        htmlLabels: true,
        curve: 'basis'
      },
      sequence: {
        useMaxWidth: true
      }
    });

    setTimeout(adaptSvgNodes, 100);
    setTimeout(adaptSvgNodes, 400);
    setTimeout(adaptSvgNodes, 1000);
  }

  // Expose functions globally for test suites & hooks
  window.initMermaid = initMermaid;
  window.adaptSvgNodes = adaptSvgNodes;

  // Hook into DOM ready
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initMermaid);
  } else {
    initMermaid();
  }

  // Observe theme attribute changes for real-time mode toggle
  function setupThemeObserver() {
    if (!document.body) return;
    const observer = new MutationObserver(function(mutations) {
      mutations.forEach(function(m) {
        if (m.attributeName === 'data-md-color-scheme') {
          adaptSvgNodes();
        }
      });
    });
    observer.observe(document.body, { attributes: true, attributeFilter: ['data-md-color-scheme'] });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', setupThemeObserver);
  } else {
    setupThemeObserver();
  }
})();
