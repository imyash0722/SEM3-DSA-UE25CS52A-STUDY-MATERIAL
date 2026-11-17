document.addEventListener('DOMContentLoaded', function() {
  if (typeof mermaid !== 'undefined') {
    // Detect current color scheme
    const isDark = document.body.getAttribute('data-md-color-scheme') === 'slate';
    
    mermaid.initialize({
      startOnLoad: true,
      theme: isDark ? 'dark' : 'default',
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
  }
});

// Re-render Mermaid diagrams when navigating (for SPA-like behavior)
if (typeof mermaid !== 'undefined') {
  document.addEventListener('DOMContentLoaded', function() {
    mermaid.init(undefined, document.querySelectorAll('.mermaid'));
  });
}

// Re-render Mermaid diagrams when theme changes
const observer = new MutationObserver(function(mutations) {
  mutations.forEach(function(mutation) {
    if (mutation.attributeName === 'data-md-color-scheme') {
      const isDark = document.body.getAttribute('data-md-color-scheme') === 'slate';
      if (typeof mermaid !== 'undefined') {
        mermaid.initialize({
          startOnLoad: true,
          theme: isDark ? 'dark' : 'default',
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
        // Re-render all mermaid diagrams
        document.querySelectorAll('.mermaid').forEach(function(el) {
          // Clear the rendered SVG
          el.innerHTML = el.textContent;
          el.classList.remove('mermaid-rendered');
        });
        mermaid.init(undefined, document.querySelectorAll('.mermaid'));
      }
    }
  });
});

observer.observe(document.body, {
  attributes: true,
  attributeFilter: ['data-md-color-scheme']
});