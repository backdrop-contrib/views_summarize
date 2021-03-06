<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>
<table <?php if ($classes) { print 'class="' . implode(' ', $classes) . '" '; } ?><?php print implode(' ', $attributes); ?>>
  <?php if (!empty($title)) : ?>
    <caption><?php print $title; ?></caption>
  <?php endif; ?>

  <thead>
    <tr>
      <?php foreach ($header as $field => $label): ?>
        <th <?php if ($header_classes[$field]) { print 'class="' . implode(' ', $header_classes[$field]) . '" '; } ?>>
          <?php print $label; ?>
        </th>
      <?php endforeach; ?>
    </tr>
  </thead>

  <?php if (empty($summary_only)): ?>
    <tbody>
      <?php if (!empty($summary_above)): ?>
        <tr class="summary">
          <?php foreach ($summarized as $field => $label): ?>
            <td><?php if (!empty($summarized[$field])) { echo $summarized[$field]; } ?></td>
          <?php endforeach; ?>
        </tr>
      <?php endif; ?>

      <?php foreach ($rows as $count => $row): ?>
        <tr class="<?php print implode(' ', $row_classes[$count]); ?>">
          <?php foreach ($row as $field => $content): ?>
            <td <?php if ($field_classes[$field][$count]) { print 'class="' . implode(' ', $field_classes[$field][$count]) . '" '; } ?><?php if ($field_attributes[$field][$count]) { print drupal_attributes($field_attributes[$field][$count]); } ?>>
              <?php print $content; ?>
            </td>
          <?php endforeach; ?>
        </tr>
      <?php endforeach; ?>
    </tbody>
  <?php endif; ?>

  <?php if (!empty($summary_below)): ?>
    <tfoot>
      <tr class="summary <?php print implode(' ', end($row_classes)); ?>">
        <?php foreach ($summarized as $summary): ?>
          <td <?php if (!empty($field_classes[$field])) { print 'class="' . implode(' ', end($field_classes[$field])) . '" '; } ?>>
            <?php if (!empty($summary)) { echo $summary; } ?>
          </td>
        <?php endforeach; ?>
      </tr>
    </tfoot>
  <?php endif; ?>
</table>
